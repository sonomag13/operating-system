
"""
Ref.:
https://stackoverflow.com/questions/21143162/python-wait-on-all-of-concurrent-futures-threadpoolexecutors-futures
"""
from concurrent.futures import ThreadPoolExecutor
import random
import time


def worker_1(*args):
    """
    :param args: there should be 2 arguments
                - 1st argument: the dictionary where we insert the result (key: index; val: sleep time)
                - 2nd argument: index
    :return: n/a
    """
    val = random.randint(1, 5)
    print("[worker 1] i = {} and val = {}".format(args[1], val))
    time.sleep(val)
    args[0].update({args[1]: val})


def worker_2(**kwargs):
    """
    :param kwargs: there should be 2 arguments:
                - key "idx" points to the current index
                - key "working_dict" points to the dictionary where we insert the result (key: index; val: sleep time)
    :return: n/a
    """
    val = random.randint(1, 8)
    print("[worker 2] i = {} and val = {}".format(kwargs["idx"], val))
    time.sleep(val)
    kwargs["working_dict"].update({kwargs["idx"]: val})


def print_dictionary(input_dict, idx):
    """
    :param input_dict: a dictionary to print
    :param idx: the index of the dictionary
    :return: n/a
    """
    print("\n\nworking dict {}".format(idx))
    for key, val in input_dict.items():
        print("\tkey = {} and val = {}".format(key, val))


def main():

    # dictionaries are passed by reference
    working_dict_1 = {}
    working_dict_2 = {}

    # initialize the pool of threads
    pool = ThreadPoolExecutor(max_workers=3)
    num = 20
    for i in range(num):
        pool.submit(worker_1, working_dict_1, i)
        pool.submit(worker_2, working_dict=working_dict_2, idx=i)

    # shutdonw ensures all the task in the pool to be completed
    pool.shutdown(wait=True)

    print_dictionary(working_dict_1, 1)
    print_dictionary(working_dict_2, 2)


if __name__ == '__main__':
    main()
    