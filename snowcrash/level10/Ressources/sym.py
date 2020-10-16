from subprocess import call

while True:
    call(["ln", "-fs", "/home/user/level10/token", "/tmp/dummy"])
    call(["ln", "-fs", "/tmp/abc", "/tmp/dummy"])
