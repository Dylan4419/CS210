#Creator: Dylan Coulter
#Assignment: Project 3
#Date: 02/18/2022
import re
import string
import os.path
from os import path


def Count_All():
    #Opens the file in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Creates an empty dictionary 
    dictionary = dict()

    #Check each line of the input file
    for line in text:
        #Strips errant spaces and newline characters
        line = line.strip()

        #Converts all characters to lowercase for easier matching
        word = line.lower()
        
        #Checks if the word already appears in the dictionary
        if word in dictionary:
            #Increment number of times the word appears
            dictionary[word] = dictionary[word] + 1
        else:
            #If the the word does not appear in the dictionary it will add it with a value of 1
            dictionary[word] = 1

    #Prints all of the contents of the dictionary
    for key in list (dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])

    #Close the opened file.
    text.close()

def Count_Instances(srch_Term):

    #Converts user input to lower case to be better matched
    Srch_Term = srch_Term.lower()

    #Opens file CS210_Project_Three_Input_File in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Creates variable word_Count to track the number of times the word has been found 
    Word_Count = 0

    #Checks every line of the input file 
    for line in text:
        #Strips any errant spaces and newline characters
        line = line.strip()

        #Converts all of the characters to lowercase for easier matching
        word = line.lower()
        
        #Checks if the found word matches the users input
        if word == srch_Term:
            #Increment number of times the word appears
            Word_Count += 1

    #Return the number of times the search term was found, as per specification
    return word_Count

    #Close opened file
    text.close()

def Collect_Data():
    #Opens file CS210_Project_Three_Input_File in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Creates and writes the file frequency.dat
    frequency = open("frequency.dat", "w")

    #Creates an empty dictionary to store found words
    dictionary = dict()

    #Checks each line of the input file
    for line in text:
        #strips any errant spaces and newline characters
        line = line.strip()

        #Convert all of the characters to lowercase for easier matching
        word = line.lower()
        
        #Check see if the word is already in the dictionary
        if word in dictionary:
            #Increment number of times the word appears
            dictionary[word] = dictionary[word] + 1
        else:
            #If the word is not already in the dictionary it adds it with a value of 1
            dictionary[word] = 1

    #Write each key and value pair to frequency.dat
    for key in list (dictionary.keys()):
        #Formats the key-value pair to  strings and ends with a newline.
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    #Close the opened files
    text.close()
    frequency.close()

