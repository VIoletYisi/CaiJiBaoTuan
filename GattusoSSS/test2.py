import random
message = input(">")
judgement = message.split(" ")
if judgement[0] == "check":
    try:
        capacity = int(judgement[1])
        value = random.randint(1, 100)
        subject = judgement[2]
        if value <= capacity:
            if value <= 5:
                print(f"{subject} {value}/{capacity} Wow! A great success!")
            else:
                print(f"{subject} {value}/{capacity} Congratulations!")
        else:
            if value > 95:
                print(f"{subject} {value}/{capacity} That's so bad! A great failure!")
            else:
                print(f"{subject} {value}/{capacity} I feel sorry to tell you that you fail.")
    except ValueError:
        print("Invalid entering!")
else:
    print("Invalid entering!")