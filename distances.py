import argparse
# import numpy
# from heapq import heappop, heappush

from matplotlib import pyplot

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

    for line in args.in_file:
    	params = [int(x) for x in line.strip().split(" ")]
    	start = (params[0], params[1])
    	end = (params[2], params[3])
    	distances.append(manhattan_distance(start, end))
    	starts.append(start)
    	ends.append(end)
    	num += 1

    pyplot.plot([s[0] for s in starts], [s[1] for s in starts], 'o')
    pyplot.show()
