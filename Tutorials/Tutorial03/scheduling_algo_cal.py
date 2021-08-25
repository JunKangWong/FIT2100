# -*- coding: utf-8 -*-
"""
Created on Tue Aug 24 17:09:29 2021

@author: jkwon
"""
from math import inf

# first come first serve
def cal_fcfs(start: int, numlst: list):
    lst = numlst[::]
    return lst, cal_avg_seek_length(lst)


# naive way of generating ssf sequence
def cal_ssf_seq(start:int, numlst:list):
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


# Optimised SSF 
def cal_ssf_opt(start: int, numlst: list):
    # sort list on ascending order, so element that are closest to each other
    # is arranged side by side
    lst = sorted(numlst[::])    
    
    # retrieve current, left and right pointers
    cur_pos = lst.index(start)
    current = lst[cur_pos]
    l, r = cur_pos - 1, cur_pos + 1
    res = [start]
    
    # this func calculates distance of 2 numbers
    def cal_distance(a:int, b:int):
        return abs(a-b)
   
    # while both l and r pointers havent reaches the end
    while(not(l < 0 and r >= len(lst))):
        # if left reaches the end, increment right
        if (l < 0):
            cur_pos = r
            r += 1
            
        # if right reaches the end increment left
        elif (r >= len(lst)):
            cur_pos = l
            l -= 1
        else:
            # if none of the pointers reaches the edge, compare which is closer.
            # if left close, choose left
            if (cal_distance(current,l) < cal_distance(current, r)):
                cur_pos = l
                l -= 1
            else: # else choose right
                cur_pos = r
                r += 1
                
        # update current value and append into list
        current = lst[cur_pos]
        res.append(lst[cur_pos])
    
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
    ssf = cal_ssf_opt(start, lst)
    print("SSF     : ", ssf[0], ssf[1])
    
    print("\nElevator")
    elevator = cal_elevator_seq(start, lst, reverse)
    print("Elevator: ", elevator[0], elevator[1])
    
    print("\nCircular Scan (C-Scan)")
    c_scan = cal_c_scan(start, lst, reverse)
    print("C_Scan  : ", c_scan[0], c_scan[1])
    


if __name__ == "__main__":
    start = 89
    
    print("With Start Point")
    list1 = [start, 125, 112, 15, 190, 137, 56, 12, 89, 38, 164, 133]
    display_all(start, list1, True)
    
    # print()
    # print("Without Start Point")
    #list2 = [125, 112, 15, 190, 137, 56, 12, 89, 38, 164, 133]
    # display_all(start, list2, True)
    
    # print("##############################")
    # print(cal_ssf_seq(89, list1))
    # print(cal_ssf_opt(89, list1))

    
    
    
    
    