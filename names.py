import pandas as pd
with open('Word Bank.csv', mode='r') as file:
    df = pd.read_csv(file)
    removed_list_num = []
    removed_list_names = []
    header = list(df.columns)
    for col_name in header:
        response = input(f"Do you want this category: {col_name}? (yes/no) ")
        if response.lower() == "n":
            removed_list_num.append(col_name) 
        elif response.lower() == "y":
            continue  # No action needed
    for col_name in removed_list_num:
        df.drop(columns=[col_name], inplace=True)
    df.to_csv('Secret_Word_Bank.csv',header = False, index=False)








"""
Legacy keep for later
import csv
import random
import pandas as pd
import io
with open('Word Bank.csv', mode ='r')as file:
  df = pd.read_csv(file)
  removed_list_num = []
  removed_list_names=[]
  header = pd.DataFrame(df.head(0))
  for x in range (header[header.columns[0]].count()):
      print (header[header.columns[x]])
      response = input("Do you want this category? ")
      if (response == "no"):
        removed_list_num.append(x)
      elif(response =='yes'):
        continue

  for x in removed_list_num:
      removed_list_names.append(header[header.columns[x]])
  for word in removed_list_names:
      temp_word = removed_list_names[word]
      header.drop(columns=[temp_word])
  for drop in header:
      temp_drop = header[drop]
      df.drop(temp_drop, axis = 1)
  df.to_csv('Secret_Word_Bank.csv', index = False)"""
  

     
        