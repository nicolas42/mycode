"""
99 bottles of beer programming language challenge
http://www.99-bottles-of-beer.net/lyrics.html
"""

d = [ 99, " bottles of beer", " on the wall", ", ", ".\n", "Take one down and pass it around, ", 98, #0-6
      " bottle of beer", "no more", "No more", "Go to the store and buy some more, ", 99 ] #7-11

sx = [
    [ [0, 1, 2, 3, 0, 1, 4,  5, 6, 1, 2, 4], 97 ], 
    [ [0, 1, 2, 3, 0, 1, 4,  5, 6, 7, 2, 4], 1 ], #2 bottles
    [ [0, 7, 2, 3, 0, 7, 4,  5, 8, 1, 2, 4], 1 ], #1 bottle 
    [ [9, 1, 2, 3, 8, 1, 4,  10, 11, 1, 2, 4], 1 ], #no more bottles
]

for s in sx:
    for i in range(s[1]):
        for n in s[0]:
            print(d[n],end='')
        print("")
        d[0]=d[0]-1
        d[6]=d[6]-1


