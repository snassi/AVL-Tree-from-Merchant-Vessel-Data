# AVL Tree from Merchant Vessel Data

This AVL Tree imports information from ``input.csv`` file with this format:
 - 200 rows (``x = 200``)
 - each row has 25 columns
 - the first column of all rows past row 2 has a country name 

Algorithm / procedure:
 - each row is uploaded to a countainer class that stores each row
 - each element of the container class is uploaded to a liked list class that is parented by the templated ``MasterCell`` class 
 - each element of the ``MasterCell`` linkedlist class is uploaded to the ``HashTabl`` class 
 - each HashNode of the ``HashTable`` is uploaded to the self-balancing AVL Tree class

Features:
 - the AVL tree has an insertion and deletion method 
 - each class is templated
