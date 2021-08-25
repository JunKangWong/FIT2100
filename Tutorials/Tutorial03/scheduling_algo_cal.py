# -*- coding: utf-8 -*-
"""
Created on Tue Aug 24 17:09:29 2021

@author: jkwon
"""
from math import inf


def cal_fcfs(start: int, numlst: list):
    lst = numlst[::]
    return lst, cal_avg_seek_length(lst)


# naive_version
def cal_ssh_seq(start:int, numlst:list):
    res, current = [], start
    lst = numlst[::]
    
    def get_closest(current, lst):
        closest, closest_ind = inf, None
        
        for i in range(len(lst)):
            
            if(abs(current - lst[i]) < closest):
                closest = abs(current - lst[i])
                closest_ind = i
                
        return closest_ind
    
    while(lst):
        index = get_closest(current, lst)
        current = lst.pop(index)
        res.append(current)
    
        
    return res, cal_avg_seek_length(res)


def cal_elevator_seq(start:int, numlst:list, reverse:bool):
    lst = sorted(numlst[::], reverse=reverse) 
    start_i = lst.index(start)
    res = lst[start_i:] + lst[start_i-1::-1]
    return res, cal_avg_seek_length(res)


def cal_c_scan(start:int, numlst:list, reverse:bool):
    lst = sorted(numlst[::], reverse=reverse)
    start_i = lst.index(start)
    res = lst[start_i:] + lst[:start_i]
    return res, cal_avg_seek_length(res)


def cal_avg_seek_length(lst:list):
    res = 0
    for i in range(len(lst)-1):
        print("|", lst[i+1],"-",lst[i], "| =", abs(lst[i+1] - lst[i]))
        res += abs(lst[i+1] - lst[i])
    print()
    return res/(len(lst)-1)


def display_all(start:int, lst:list, reverse:bool):
    print("\nFirst Come First Serve (FCFS)")
    fcfs = cal_fcfs(start, lst)
    print("FCFS    : ", fcfs[0], fcfs[1])
    
    print("\nShortest Seek First (SSF)")
    ssh = cal_ssh_seq(start, lst)
    print("SSF     : ", ssh[0], ssh[1])
    
    print("\nElevator")
    elevator = cal_elevator_seq(start, lst, reverse)
    print("Elevator: ", elevator[0], elevator[1])
    
    print("\nCircular Scan (C-Scan)")
    c_scan = cal_c_scan(start, lst, reverse)
    print("C_Scan  : ", c_scan[0], c_scan[1])
    


if __name__ == "__main__":

    list1 = [89, 125, 112, 15, 190, 137, 56, 12, 89, 38, 164, 133]
    list2 = [125, 112, 15, 190, 137, 56, 12, 89, 38, 164, 133]
    start = 89
    
    print("Test1")
    display_all(start, list1, True)
    print()
    print("Test2")
    display_all(start, list2, True)

    
    
    
    
    