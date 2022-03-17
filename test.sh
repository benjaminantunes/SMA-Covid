#!/bin/bash  
#Script to print 11th character of a String  
    
str="configLyon.txt"  
substr="${str: 0 :-4}"  
echo "$substr"  
