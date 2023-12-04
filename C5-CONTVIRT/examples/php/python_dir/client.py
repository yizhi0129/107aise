import redis
import string

with open("getp.txt", "r") as f:
    data = f.read()

words=[]

lines = data.split("\n")


for l in lines:
    l = l.translate(str.maketrans('','', string.punctuation))
    words = words + l.split(" ")


r = redis.Redis(host="myredis",port=6379)

for w in words:
    print(w)
    r.hincrby("words", w, 1)


