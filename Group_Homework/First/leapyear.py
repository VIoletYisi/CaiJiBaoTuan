date = '2400-3-15'
numbers = date.split('-')
numbers = [int(numbers[i]) for i in range(3)]
year_difference = numbers[0] - 1900
leap_year = year_difference // 4 - year_difference // 100
if year_difference >= 100:
    leap_year = leap_year + year_difference // 400 + 1
days_for_year = leap_year * 366 + (numbers[0] - leap_year) * 365
leap_year