# start timer
import time

start = time.time()
for i in range(1000000):
    # do nothing
    pass

end = time.time()
print("Time taken in microseconds: ", (end-start)*1000000)
