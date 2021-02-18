############################################################################################################
# There are n lockers in a hallway, numbered sequentially from 1 to n. Initially, all the locker doors     #
# are closed. You make n passes by the lockers, each time starting with locker #1. On the ith iteration    #
# you toggle the door of each ith locker. If the door is closed, you open it; if it is open, you close it. #
# After the last pass, which locker doors are openand which are closed? How many of them are open?         #
############################################################################################################

n = int(input("input n: "))

lockers = [False for _ in range(n)]

for i in range(n):
    for j in range(n):
        if (j+1) % (i+1) == 0:
            lockers[j] = not lockers[j]

open_lockers = [idx + 1 for idx, _open in enumerate(lockers) if _open]

print(f"Lockers {open_lockers} are open, {len(open_lockers)}/{n} total")