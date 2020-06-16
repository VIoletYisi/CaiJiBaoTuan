//)
// Solution to the one-dimensional Schroedinger equation with various potential functions 
// Uses matching method
//
// Producing Figures such as 10.13, pages 321
//
// Version December 8, 9:30 PM
//  Additions for displaying the rescaled energy level
//  Replacement of the "huntDirection" option by the "psiParity" option
//  Addition of square well (3), power law (4), and anharmonic potentials (5) choices
//  Uses Numerov iteration method by default
//  Addition of cosine dependent potential (6) for final exam project question 2.
//
#include <cstdlib>    // needed for random number generator
#include <ctime>      // needed to get current time of day
#include <iostream>   // needed for standard input and output
#include <iomanip>
#include <fstream>    // needed for writing and reading files
#include <math.h>

#include "gprocess.h" // needed for graphics package

using namespace std;

bool useNumerov = true;

double XLEFT = 0.5;     // left mostposition
double XRIGHT = +5.0;   // rightmost position
double XMATCH = 1.40;   // Location of matching point
double XMATCH_WINDOW = 0.25; // window around matching point where left and right solutions will overlap

double vScale = 10.0;   // vScale for the potential
double eGuess = -1.5;   // guess for eigenvalue energy
double eDelta = 0.25;   // delta energy change for convergence
double derivativeDifferenceCheck = 0.01; // criterion to check for equal derivatives for left and right solutions
int psiParity = +1;     // assumed parity

unsigned int vType = 1;  // 1 = Lennard-Jones potential (with sigma = 1), 2 = harmonic oscillator (with m = 1)

double xDelta = 0.001;  // delta-X in iteration
double xDeltaSquared2 = 2.0*xDelta*xDelta;
unsigned int nPoints = int((XRIGHT - XLEFT)/xDelta);  // goes out to the box boundary
unsigned int JMATCH = int((XMATCH-XLEFT)/xDelta);     // index in wave function array for position of match point

double vPotential(const double xPosition) {
 
  double potentialValue;

  if(vType==1) // Lennard-Jones potential
    potentialValue = 4.0*vScale*(pow(xPosition, -12.) - pow(xPosition, -6.));
 
  if(vType==2) // harmonic oscillator potential
    potentialValue = 0.5*vScale*xPosition*xPosition;

  if(vType==3) { // square well, height = vScale
    if(fabs(xPosition) <= 0.5*XRIGHT)
      potentialValue = 0.0;
   else
      potentialValue = vScale;
  }

  if(vType==4) // power law potential
    potentialValue = pow(xPosition,vScale);

  if(vType==5) // anharmonic potential
    potentialValue = 0.5*vScale*(pow(xPosition,2.0) + 0.1*pow(xPosition,4.0));

  if(vType==6) { // well with cosine dependence
    if(fabs(xPosition)<0.5) 
      potentialValue = -0.5*vScale*(1.0 + cos(2.0*M_PI*xPosition));
    else
      potentialValue = 0.0;
  }
    

  return potentialValue;

} 

void findTurningPoints(double energyValue, double *leftTurningPoint, double *rightTurningPoint) {

  if(vType==3) { // special case for square well
    *leftTurningPoint = 0.5*XLEFT;
    *rightTurningPoint = 0.5*XRIGHT;
    return;
  }

  double equalValue = 0.03*fabs(energyValue);
  double xPosition = XLEFT;
  *leftTurningPoint = XRIGHT;
  for(unsigned int j=0; j<10*nPoints; j++) {
    if(fabs(vPotential(xPosition) - energyValue) < equalValue) {
      *leftTurningPoint = xPosition;
      break;
    }
    xPosition += 0.1*xDelta;
  }

  xPosition = XRIGHT;
  *rightTurningPoint = XLEFT;
  for(unsigned int j=0; j<10*nPoints; j++) {
    if(fabs(vPotential(xPosition) - energyValue) < equalValue) {
      *rightTurningPoint = xPosition;
      break;
    }
    xPosition -= 0.1*xDelta;
  }

  return;

}

void graphPsiFunction(double *psiFunctionLeft, double *psiFunctionRight, unsigned int lPoints,  unsigned int rPoints, unsigned mPoints,
		      const double currentEnergy, const double currentDeltaE,
		      const unsigned int kCount, const unsigned int iCase);

int main(int argc, char* argv[]) {

  if(argc==2 && strcmp(argv[1], "help")==0) {
    cout << "\n\n Program " << argv[0];
    cout << "\n Optional input arguments (defaults in parentheses)";
    cout << "\n  eGuess (=-1.5), eDelta (=0.25), vType (=1), vScale (=10.), derivativeDifferenceCheck (=0.01), psiParity (=+1), xDelta (=0.001)";
    cout << endl << endl;
    return 0;
  }

  if(argc > 1) {
    eGuess= atof(argv[1]);
    cout << "\n Input eGuess = " << eGuess;
  }
  else {
    cout << "\n Default eGuess = " << eGuess;
  }

  if(argc > 2) {
    eDelta= atof(argv[2]);
    cout << "\n Input eDelta = " << eDelta;
  }
  else {
    eDelta= 0.25;
    cout << "\n Default eDelta = " << eDelta;
  }

  if(argc > 3) {
    vType = atoi(argv[3]);
    if(vType == 1) {
      cout << "\n Input vType = " << vType << " corresponds to Lennard-Jones potential";
    }

    if(vType == 2) {
      if(eGuess <= 0.0 || eGuess + eDelta <=0.0) {
        cerr << "\n Cannot use harmonic potential with eGuess = " << eGuess;
        cerr << ", or eGuess + eDelta = " << eGuess + eDelta;
        cerr << endl;
        exit(1);  // safety check
      }
      else {
        XRIGHT = 4.0*sqrt(2.0*(eGuess + eDelta));
        XLEFT = -XRIGHT;
      }
      XMATCH = 0.25*XRIGHT;
      cout << "\n Input vType = " << vType << " corresponds to harmonic oscillator potential";
    }

    if(vType == 3) {
      XLEFT = -2.0;
      XRIGHT = +2.0;
      XMATCH = 0.25*XRIGHT;
      cout << "\n Input vType = " << vType << " corresponds to square well potential";
    }

    if(vType == 4) {
      if(eGuess <= 0.0 || eGuess + eDelta <=0.0) {
        cerr << "\n Cannot use power law potential with eGuess = " << eGuess;
        cerr << ", or eGuess + eDelta = " << eGuess + eDelta;
        cerr << endl;
        exit(1);  // safety check
      }
      else {
        XRIGHT = 4.0*sqrt(2.0*(eGuess + eDelta));
        XLEFT = -XRIGHT;
      }
      XMATCH = 0.25*XRIGHT;
      cout << "\n Input vType = " << vType << " corresponds to power law potential, V = x**" << vType;
    }

    if(vType == 5) {
      if(eGuess <= 0.0 || eGuess + eDelta <=0.0) {
        cerr << "\n Cannot use anharmonic potential with eGuess = " << eGuess;
        cerr << ", or eGuess + eDelta = " << eGuess + eDelta;
        cerr << endl;
        exit(1);  // safety check
      }
      else {
        XRIGHT = 2.0*sqrt(2.0*(eGuess + eDelta));
        XLEFT = -XRIGHT;
      }
      XMATCH = 0.25*XRIGHT;
      cout << "\n Input vType = " << vType << " corresponds to anharmonic potential, with K2 = " << vType;
    }

    if(vType == 6) {
      XLEFT = -12.0;
      XRIGHT = +12.0;
      XMATCH = 0.05*XRIGHT;
      cout << "\n Input vType = " << vType << " corresponds to square well potential with cosine dependence";
    }

  }
  else {
    cout << "\n Default vType = " << vType << " corresponds to Lennard-Jones potential";
  }

  if(argc > 4) {
    vScale= atof(argv[4]);
    cout << "\n Input vScale = " << vScale;
  }
  else {
    cout << "\n Default eDelta = " << eDelta;
  }

  if(argc > 5) {
    derivativeDifferenceCheck= atof(argv[5]);
    cout << "\n Input derivativeDifferenceCheck = " << derivativeDifferenceCheck;
  }
  else {
    cout << "\n Default derivativeDifferenceCheck = " << derivativeDifferenceCheck;
  }

  if(argc > 6) {
    if(atoi(argv[6])==1) {
      psiParity = +1;
      cout << "\n Input psiParity = " << psiParity;
    }
    if(atoi(argv[6])==-1) {
      psiParity = -1;
      cout << "\n Input psiParity = " << psiParity;
    }
    if(atoi(argv[6])!=1 && atoi(argv[6])!=-1) {
      cerr << "\n Input parity value " << atoi(argv[6]) << " is not permitted" << endl;
      exit(1);
    }
  }
  else {
    cout << "\n Default psiParity = " << psiParity;
  }

  if(argc > 7) {
    xDelta= atof(argv[7]);
    if(xDelta < 0.0) {
      xDelta = -xDelta;
      useNumerov = false;
    }
    cout << "\n Input xDelta = " << xDelta;
    xDeltaSquared2 = 2.0*xDelta*xDelta;
  }
  else {
    cout << "\n Default xDelta = " << xDelta;
  }
  nPoints = int((XRIGHT - XLEFT)/xDelta);
  cout << "\n Number of spatial points to boundary = " << nPoints + 1;
  if(useNumerov)
    cout << "\n Using the Numerov iteration algorithm with fifth order accuracy";
  else
    cout << "\n Using the original, second order finite difference iteration algorithm";

  JMATCH = int((XMATCH-XLEFT)/xDelta);

  double xDeltaSquaredDivide12 = xDelta*xDelta/12.0;
  double xDeltaSquaredTimes5Divide12 = 5.0*xDeltaSquaredDivide12;

  cout << endl;
  //
  // Finished input arguments check
  //

  double *psiFunctionLeft = new double[nPoints];  // array to contain the left side solution
  double *psiFunctionRight = new double[nPoints]; // array to contain the right side solution

  for(unsigned int j=0; j<nPoints; j++) {
    psiFunctionLeft[j] = -2.0;
    psiFunctionRight[j] = -2.0;
  } // dummy initialization;

  //
  // real initialization for two points at either end
  //
  psiFunctionLeft[0] = 0.0;
  psiFunctionLeft[1] = 0.0001*xDelta*psiParity;
  psiFunctionRight[nPoints-1] = 0.0;
  psiFunctionRight[nPoints-2] = 0.0001*xDelta;

  bool notOverLimit = true;
  bool notConverged = true;
  unsigned int kCount = 0;
  double lastDifference = 0.0;

  //
  // loop over the energy guesses
  //
  while(notConverged && notOverLimit) {
    double xPositionLeft = XLEFT + xDelta;
    double xPositionRight = XRIGHT - xDelta;

    double vPotentialLeft;
    double vPotentialRight;

    double leftMax = 0.0;
    double rightMax = 0.0;

    unsigned int leftPoints = 0;
    unsigned int rightPoints = 0;

    //
    // iteration loop using a particular energy guess
    //
    for (unsigned int j=2; j<nPoints; j++) {

      //
      // check if x value is still below match point for left solution
      //
      if(xPositionLeft - XMATCH <= XMATCH_WINDOW) {
        leftPoints++;
	vPotentialLeft = vPotential(xPositionLeft);

        if(useNumerov) {
          double kSquaredCurrent = 2.0*(eGuess - vPotentialLeft); // assumes hbar = 1, and mass m = 1
          double kSquaredPrevious = 2.0*(eGuess - vPotential(xPositionLeft - xDelta)); // assumes hbar = 1, and mass m = 1
          double kSquaredNew = 2.0*(eGuess - vPotential(xPositionLeft + xDelta)); // assumes hbar = 1, and mass m = 1
          double fact1 = 2.0*(1.0 - xDeltaSquaredTimes5Divide12*kSquaredCurrent);
          double fact2 = 1.0 + xDeltaSquaredDivide12*kSquaredPrevious;
          double fact3 = 1.0 + xDeltaSquaredDivide12*kSquaredNew;
          if(fact3 !=0.0) {
            psiFunctionLeft[j] = (fact1*psiFunctionLeft[j-1] - fact2*psiFunctionLeft[j-2])/fact3;
          }
          else {
            cerr << "\n Attempted divide by 0 in the Numerov iteration algorithm, for left solution" << endl;
            exit(1);
          } // divide by 0 safety check
        }
        else {
          psiFunctionLeft[j] = 2.0*psiFunctionLeft[j-1] - psiFunctionLeft[j-2] - xDeltaSquared2*(eGuess - vPotentialLeft)*psiFunctionLeft[j-1];
        }

        if(fabs(psiFunctionLeft[j]) > leftMax)
          leftMax = fabs(psiFunctionLeft[j]);

        xPositionLeft += xDelta; // x-value for continuing iteration loop for left side solution
      } // left side check

      //
      // check if x value is still above match point for right solution
      //
      if(XMATCH - xPositionRight <= XMATCH_WINDOW) {
        rightPoints++;
	vPotentialRight = vPotential(xPositionRight);

        if(useNumerov) {
          double kSquaredCurrent = 2.0*(eGuess - vPotentialRight); // assumes hbar = 1, and mass m = 1
          double kSquaredPrevious = 2.0*(eGuess - vPotential(xPositionRight + xDelta)); // assumes hbar = 1, and mass m = 1
          double kSquaredNew = 2.0*(eGuess - vPotential(xPositionRight - xDelta)); // assumes hbar = 1, and mass m = 1
          double fact1 = 2.0*(1.0 - xDeltaSquaredTimes5Divide12*kSquaredCurrent);
          double fact2 = 1.0 + xDeltaSquaredDivide12*kSquaredPrevious;
          double fact3 = 1.0 + xDeltaSquaredDivide12*kSquaredNew;
          if(fact3 !=0.0) {
            psiFunctionRight[nPoints-j-1] = (fact1*psiFunctionRight[nPoints-j] - fact2*psiFunctionRight[nPoints-j+1])/fact3;
          }
          else {
            cerr << "\n Attempted divide by 0 in the Numerov iteration algorithm, for right solution" << endl;
            exit(1);
          } // divide by 0 safety check
        }
        else {
          psiFunctionRight[nPoints-j-1] = 2.0*psiFunctionRight[nPoints-j] - psiFunctionRight[nPoints-j+1] - xDeltaSquared2*(eGuess - vPotentialRight)*psiFunctionRight[nPoints-j];
        }

        if(fabs(psiFunctionRight[nPoints-j-1]) > rightMax)
          rightMax = fabs(psiFunctionRight[nPoints-j-1]);

        xPositionRight -= xDelta; // x-value for continuing iteration loop for right side solution
      } // right side check

      if(xPositionLeft - XMATCH > XMATCH_WINDOW &&
         XMATCH - xPositionRight > XMATCH_WINDOW) {

        //
        // normalize the wave functions to have their maxima at 1
        //
        for(unsigned int i=0; i<leftPoints; i++) {
          psiFunctionLeft[i] /= leftMax;
        }
        for(unsigned int i=1; i<=rightPoints; i++) {
          psiFunctionRight[nPoints - i] /= rightMax;
        }
        if(lastDifference == 0.0)  // plot solutions from initial iteration, before matching
          graphPsiFunction(psiFunctionLeft, psiFunctionRight, leftPoints, rightPoints, nPoints, eGuess, eDelta, kCount, 0);

        break; // break out of iteration

      } // check on completing overlap window

    } // iteration loop 

    double psiLeftMatch = psiFunctionLeft[JMATCH];
    double psiRightMatch = psiFunctionRight[JMATCH];
    double matchRatio = psiLeftMatch/psiRightMatch;
    //
    // Normalize the right function to the left function at the matching point
    //
    for(unsigned int i=1; i<=rightPoints; i++) {
      psiFunctionRight[nPoints - i] *= matchRatio;
    }

    //
    // currentDifference is the current difference between the left and the right derivatives
    //
    double currentDifference = (psiFunctionLeft[JMATCH+1] - psiFunctionLeft[JMATCH]) - (psiFunctionRight[JMATCH+1] - psiFunctionRight[JMATCH]);
    currentDifference /= xDelta;
    double meanDerivative = (psiFunctionLeft[JMATCH+1] - psiFunctionLeft[JMATCH]) + (psiFunctionRight[JMATCH+1] - psiFunctionRight[JMATCH]);
    meanDerivative /= (2.0*xDelta);

    if(fabs(currentDifference) < derivativeDifferenceCheck*fabs(meanDerivative)) {
      notConverged = false;
      cout << "\n Derivative ratio check value achieved ";
      cout << " eGuess = " << eGuess << ", eDelta = " << eDelta;
      cout << endl;
      graphPsiFunction(psiFunctionLeft, psiFunctionRight, leftPoints, rightPoints, nPoints, eGuess, eDelta, kCount, 1);
    }

    if(lastDifference==0) {
      //
      // special guess of the first energy guess
      //
      if(currentDifference > 0.0)
        eGuess += eDelta;
      else
        eGuess -= eDelta;
    }
    else {
      //
      // check if the left - right derivative difference has changed signs
      // if so, then halve the energy change and change its sign
      //
      if(currentDifference/lastDifference < 0.0) {
        //
        // halve the delta value and change in sign
        //
        eDelta *= 0.5;
      }
      if(currentDifference > 0.0)
        eGuess += eDelta;
      else
        eGuess -= eDelta;
    }
    lastDifference = currentDifference;

    if(kCount > 99) {
      notOverLimit = false;
      cout << "\n Reached kCount limit: ";
      cout << " eGuess = " << eGuess << ", eDelta = " << eDelta;
      cout << endl;
      graphPsiFunction(psiFunctionLeft, psiFunctionRight, leftPoints, rightPoints, nPoints, eGuess, eDelta, kCount, 2);
    }

    if(fabs(eDelta/eGuess) < 1.e-14) {
      notOverLimit = false;
      cout << "\n Reached eDelta/eGuess limit: ";
      cout << " eGuess = " << eGuess << ", eDelta = " << eDelta;
      cout << endl;
      graphPsiFunction(psiFunctionLeft, psiFunctionRight, leftPoints, rightPoints, nPoints, eGuess, eDelta, kCount, 3);
    }

    kCount++;

  } // convergence loop

  delete [] psiFunctionRight;
  delete [] psiFunctionLeft;

  return 0;

}

void graphPsiFunction(double *psiFunctionLeft, double *psiFunctionRight, unsigned int lPoints, unsigned rPoints, unsigned int mPoints,
		      const double currentEnergy, const double currentDeltaE,
		      const unsigned int kCount, const unsigned int iCase) {

  double YMAX = +2.0;
  double YMIN = -1.0;
  double XMAX = XRIGHT;
  double XMIN = XLEFT;

  double *xLeftPlot = new double [lPoints];
  double *xRightPlot = new double [rPoints];
  double *yRightPlot = new double [rPoints];
  double leftPosition = XLEFT; 
  double rightPosition = XRIGHT; 
  for(unsigned int j=0; j<lPoints; j++) {
    xLeftPlot[j] = leftPosition;
    leftPosition += xDelta;
  }
      
  for(unsigned int j=0; j<rPoints; j++) {
    xRightPlot[j] = rightPosition;
    yRightPlot[j] = psiFunctionRight[mPoints - 1 - j];
    rightPosition -= xDelta;
  } // loop over positions

  const unsigned int NAXIS = 400;
  double deltaAxis = (XMAX - XMIN)/NAXIS;
  double *xAxis = new double [NAXIS];
  double *yAxis = new double [NAXIS];
  double *yPotential = new double [NAXIS];

  double vRescale = 1.0;
  if(vType == 1)
    vRescale = -1.0/vPotential(1.12);

  if(vType == 2 || vType >= 4)
    vRescale = 2.0/vPotential(0.5*XRIGHT);

  if(vType == 3)
    vRescale = 2.0/vScale;

  if(vType == 6)
    vRescale = 1.0/vScale;

  double xPosition = XMIN;
  for(unsigned int j=0; j<NAXIS; j++) {
    xAxis[j] = xPosition;
    yAxis[j] = 0.0;

    yPotential[j] = vRescale*vPotential(xPosition);
    if(yPotential[j] > YMAX)
      yPotential[j] = YMAX;

    xPosition += deltaAxis;
  }

  {
    // This brace used to limit scope of Gprocess
    CAMgraphicsProcess  Gprocess;                 // declare a graphics process

    char caseText[80];
    char normText[80];
    char fileName[40];
    char vText[60];

    if(iCase==0) {
      sprintf (caseText, "Result of initial iteration");
      sprintf (fileName, "oneDimensionalQMInitial.ps");
    }
    else {
      sprintf (fileName, "oneDimensionalQMFinal.ps");
    }

    if(iCase==1) {
      sprintf (caseText, "Solution has converged at iteration %d",kCount);
      double normFactor = 0.0;
      xPosition = XLEFT;      
      for(unsigned int j=0; j<lPoints; j++) {
        if(xPosition > XMATCH)
          break;
	normFactor += psiFunctionLeft[j]*psiFunctionLeft[j];
        xPosition += xDelta;
      }
      xPosition = XRIGHT;      
      for(unsigned int j=0; j<rPoints; j++) {
        if(xPosition <= XMATCH)
          break;
	normFactor += psiFunctionRight[mPoints - j - 1]*psiFunctionRight[mPoints - j - 1];
        xPosition -= xDelta;
      }
      if(normFactor>0.0)
	normFactor = 1.0/(normFactor*xDelta);
      sprintf (normText, "Normalization factor = %8.3e", normFactor);
    } // check for iCase = 1

    if(iCase==2)
      sprintf (caseText, "Program ended because of iteration limit %d",kCount);

    if(iCase==3)
      sprintf (caseText, "Program ended due to Delta-E/E limit at iteration %d",kCount);

    CAMpostScriptDriver Pdriver(fileName);  // declare a PostScript driver
    Gprocess.attachDriver(Pdriver);               // Attach driver to process

    char buffer[80];
    if(vType==1)
      sprintf (buffer,"Energy=%5.3f, Delta-E=%8.3e, Lennard-Jones", currentEnergy, currentDeltaE);

    if(vType==2)
      sprintf (buffer,"Energy=%5.3f, Delta-E=%8.3e, Harmonic Oscillator", currentEnergy, currentDeltaE);

    if(vType==3)
      sprintf (buffer,"Energy=%5.3f, Delta-E=%8.3e, Square Well", currentEnergy, currentDeltaE);

    if(vType==4)
      sprintf (buffer,"Energy=%5.3f, Delta-E=%8.3e, Power Law n=%d", currentEnergy, currentDeltaE, int(vScale));

    if(vType==5)
      sprintf (buffer,"Energy=%5.3f, Delta-E=%8.3e, Anharmonic Potential", currentEnergy, currentDeltaE);

    if(vType==6)
      sprintf (buffer,"Energy=%5.3f, Delta-E=%8.3e, Modified Sq. Well", currentEnergy, currentDeltaE);

    sprintf (vText, "The potential curve is rescaled by a factor %8.3e",vRescale);

    Gprocess.title(buffer);
    Gprocess.setPlotPointSize(0.04);  // twice default size of 0.02

    Gprocess.setAxisRange(XMIN, XMAX, YMIN, YMAX);    // set plotting ranges 
    Gprocess.labelX("X-Position");
    Gprocess.labelY("psiFunction value");

    Gprocess.setPlotLineColor(CAMgraphicsProcess::BLUE);
    Gprocess.plot(xRightPlot, yRightPlot, rPoints);
    Gprocess.setPlotLineColor(CAMgraphicsProcess::GREEN);
    Gprocess.plot(xLeftPlot, psiFunctionLeft, lPoints);

    Gprocess.setPlotLineColor(CAMgraphicsProcess::RED);
    Gprocess.plot(xAxis, yPotential, NAXIS);

    Gprocess.setPlotLineColor(CAMgraphicsProcess::BLACK);
    Gprocess.plot(xAxis, yAxis, NAXIS);

    Gprocess.drawString(0.50, 0.10, caseText, 0.04);
    if(iCase==1) {
      Gprocess.drawString(0.50, 0.05, normText, 0.04);

      //
      // draw the energy level in the classically allowed region
      //
      double xEigenValue[2];
      double yEigenValue[2];
      double leftTurn;
      double rightTurn;
      findTurningPoints(currentEnergy, &leftTurn, &rightTurn);
      if(leftTurn < rightTurn) {
	xEigenValue[0] = leftTurn;
	xEigenValue[1] = rightTurn;
	yEigenValue[0] = vRescale*currentEnergy;
	yEigenValue[1] = vRescale*currentEnergy;
	Gprocess.plot(xEigenValue, yEigenValue, 2);
	Gprocess.drawString(0.50, 0.80, "The energy level position is rescaled by the same factor", 0.03);
      } // check that the turning points are in the correct order
    }

    Gprocess.drawString(0.50, 0.85, vText, 0.03);

    Gprocess.frame();                           // "frame" the plot

  } // end of CAMgraphics brace

  delete [] xLeftPlot;
  delete [] xRightPlot;
  delete [] yRightPlot;
  delete [] xAxis;
  delete [] yAxis;
  delete [] yPotential;

  return;

}
