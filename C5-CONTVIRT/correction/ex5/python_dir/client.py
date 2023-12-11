import redis
import string
import time
import hashlib

known_pass = {}


print("COUCOU LES AMIS")

with open("pwd.txt", "r") as f:
    print("Processing file")
    data = f.read()
    pwd = str(data).split("\n")

    for p in pwd:
        md5 = hashlib.md5(p.encode())
        known_pass[md5.hexdigest()] = p


def dictmd5(md5):
    print("Checking {}".format(md5.decode()))
    if md5.decode() in known_pass.keys():
        print("{} is {} compromised".format(md5, known_pass[md5.decode()]))
        return known_pass[md5.decode()]
    return None

    
print("Before redis")
r = redis.Redis(host="leredis")

print("After redis")

while True:


    users = r.hgetall("users")
    print(users)


    for k,v in users.items():
        print("Attacking {}".format(k))
        pwd = dictmd5(v)

        if pwd:
            print("{} PAWNED {}".format(k,pwd))
            r.hset("users", k, "COMP")


    time.sleep(10)

