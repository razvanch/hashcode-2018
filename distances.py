import argparse
# import numpy
# from heapq import heappop, heappush

from matplotlib import pyplot

class Ride:
    def __init__(self, start, end, earliest, latest):
        self.start = start
        self.end = end
        self.earliest = earliest
        self.latest = latest

def manhattan_distance(a, b):
    al, ac = a
    bl, bc = b
    return abs(al - bl) + abs(ac - bc)

if __name__ == "__main__":

    arg_parser = argparse.ArgumentParser()
    arg_parser.add_argument("in_file", help="Problem file", type=argparse.FileType('r'))
    # arg_parser.add_argument("--maxsteps", type=int, required=False)
    args = arg_parser.parse_args()

    # MAX_STEPS = args.maxsteps

    line = args.in_file.readline()
    distances = []
    starts = []
    ends = []
    num = 0
    rides = []

    for line in args.in_file:
    	params = [int(x) for x in line.strip().split(" ")]

    	start = (params[0], params[1])
    	end = (params[2], params[3])
        earliest, latest = (params[4], params[5])

        rides.append(Ride(start, end, earliest, latest))

    	distances.append(manhattan_distance(start, end))
    	starts.append(start)
    	ends.append(end)
    	num += 1

    # start_times = [r.earliest for r in rides if r.start[0] <= 5000]
    pyplot.plot([r.start[0] for r in rides], [r.start[1] for r in rides], 'o')
    pyplot.plot([r.end[0] for r in rides], [r.end[1] for r in rides], 'ro')
    pyplot.show()
