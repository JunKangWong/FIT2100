# -*- coding: utf-8 -*-
"""
Created on Tue Aug 24 17:09:29 2021

@author: jkwon
"""
from math import inf


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
        
    return res




def cal_elevator_seq(start:int, numlst:list, direction:bool):
    if(direction):
        lst = sorted(numlst[::])
    else:
        lst = sorted(numlst[::], reverse=True)
        
    start_i = lst.index(start) 

    return lst[start_i:] + lst[start_i-1::-1]


def cal_c_scan(start:int, numlst:list, direction:bool):
    if(direction):
        lst = sorted(numlst[::])
    else:
        lst = sorted(numlst[::], reverse=True)
        
    start_i = lst.index(start) 
    
    return lst[start_i:] + lst[:start_i]


def cal_avg_seek_length(lst:list):
    res = 0
    for i in range(len(lst)-1):
        print("|", lst[i+1],"-",lst[i], "| =", abs(lst[i+1] - lst[i]))
        res += abs(lst[i+1] - lst[i])
    print()
    return res/(len(lst)-1)


def display_all(start:int, lst:list, direction:bool):
    ssh = cal_ssh_seq(start, list1)
    elevator = cal_elevator_seq(start, list1, direction)
    c_scan = cal_c_scan(start, list1, direction)
    
    fcfs_avg = cal_avg_seek_length(lst)
    ssh_avg = cal_avg_seek_length(ssh)
    elevator_avg = cal_avg_seek_length(elevator)
    c_scan_avg = cal_avg_seek_length(c_scan)
    
    print("FCFS    : ", lst, fcfs_avg)
    print("SSF     : ", ssh, ssh_avg)
    print("Elevator: ", elevator, elevator_avg)
    print("C_Scan  : ", c_scan, c_scan_avg)
    


if __name__ == "__main__":

   # nump1 = np.array([125, 112, 15, 190, 137, 56, 12, 89, 38, 164, 133])
    list1 = [125, 112, 15, 190, 137, 56, 12, 89, 38, 164, 133]
    start = 89
    
    display_all(start, list1, False)

    
    
    
    
    