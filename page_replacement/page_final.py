from collections import OrderedDict
import sys


def runLR():
    LRU = [None] * line1[1]
    print("Page Reference Numbers: %d" % pages)
    print("LRU List Update:")
    print("#Pg", end='  : ')
    print(LRU)
    print("--------------------")
    fault = 0
    for page in referenceString:
        if page in LRU:
            LRU.remove(page)
            LRU.append(page)
            print(page, end='   : ')
            print(LRU)
        else:
            del LRU[0]
            LRU.append(page)
            fault = fault + 1
            print(page, end='   : ')
            print(LRU)
    print("\nNumber of Page Faults: %d" % fault)


def runFF():
    FIFO = [None] * line1[1]
    print("Page Reference Numbers: %d" % pages)
    print("FIFO List Update:")
    print("#Pg", end='  : ')
    print(FIFO)
    print("--------------------")
    fault = 0
    for page in referenceString:
        if page in FIFO:
            print(page, end='   : ')
            print(FIFO)
        else:
            del FIFO[0]
            FIFO.append(page)
            fault = fault + 1
            print(page, end='   : ')
            print(FIFO)

    print("\nNumber of Page Faults: %d" % fault)


def runLF():
    LFU = OrderedDict()
    print("LFU List Update:")
    print("#Pg", end='  : ')
    print(LFU)
    print("--------------------")
    fault = 0
    count = 0
    for page in referenceString:
        if page in LFU.keys():
            LFU[page] = LFU[page] + 1
            print(page, end='   : ')
            print(LFU)
        else:
            if count < frames:
                LFU.update({page: 1})
                fault = fault + 1
                print(page, end='   : ')
                print(LFU)
            else:
                swap = min(LFU, key=LFU.get)
                del LFU[swap]
                LFU.update({page: 1})
                fault = fault + 1
                print(page, end='   : ')
                print(LFU)
            count = count + 1  # to count till frame gets fill
    print("\nNumber of Page Faults: %d" % fault)


# Checking if valid commandline argument is provided or not
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Please Enter input file and search string")
        sys.exit(1)
    # Switch cases default value assignment
    if len(sys.argv) == 3:
        test = sys.argv[2]
    else:
        test = "def"

    # Reading File data into line1 and referenceString
    file_name = sys.argv[1]
    with open(file_name) as f:
        lines = f.read().splitlines()
    line1 = list(map(int, lines[0].split(' ')))
    referenceString = list(map(int, lines[1].split(' ')))
    del lines
    print(line1)
    print(referenceString)
    pages = line1[0]    # Number of pages
    frames = line1[1]   # Number of Frames

    # Switch Cases as per the input
    if test == "FF":
        runFF()
    elif test == "LF":
        runLF()
    elif test == "LR":
        runLR()
    else:
        print("#######################FF")
        runFF()
        print("#######################LF")
        runLF()
        print("#######################LR")
        runLR()
