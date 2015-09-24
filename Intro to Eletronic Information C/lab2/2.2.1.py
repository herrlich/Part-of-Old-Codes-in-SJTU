import string
import re
class Bitarray:
    def __init__(self, size):
        """ Create a bit array of a specific size """
        self.size = size
        self.bitarray = bytearray(size/8)

    def set(self, n):
        """ Sets the nth element of the bitarray """

        index = n / 8
        position = n % 8
        self.bitarray[index] = self.bitarray[index] | 1 << (7 - position)

    def get(self, n):
        """ Gets the nth element of the bitarray """

        index = n / 8
        position = n % 8
        return (self.bitarray[index] & (1 << (7 - position))) > 0

    def find_in_hash(self,words):
        for i in range(5):
            num=BKDRHash(words,i)%1000000
            if self.get(num)!=1:
                return False
        return True

def BKDRHash(key,times):
    if times==0: seed=19
    if times==1: seed=171
    if times==2: seed=4513
    if times==3: seed=27137
    if times==4: seed=137519
    hash = 0
    for i in range(len(key)):
        hash = (hash * seed) + ord(key[i])
    return hash


if __name__ == "__main__":
    bitarray_obj = Bitarray(8000000)
    total_word=0
    f = open("D://pg1661.txt",'r')
    for line in f.xreadlines():
        for word in line.strip().replace("--"," ").split(' '):
            word=string.lower(word).replace(".","").replace(",","")
            if bitarray_obj.find_in_hash(word)!=True:
                total_word+=1
                for j in range(5):
                    num=BKDRHash(word,j)%1000000
                    bitarray_obj.set(num)
    dic_word=0
    dic=open("D://dic.txt",'r')
    for line in dic.xreadlines():
        for word in line.strip().split(' '):
            if bitarray_obj.find_in_hash(word):
                dic_word+=1
    dic.close()
    f.close()
    print total_word
    print dic_word