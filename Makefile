all:
		rm -rfv tphashmap_user_test
		gcc -O3 -std=c17 -shared -o libTPhashmap.so tphashmap.c
		# The dot "." stand for the path we are in right now
		gcc -O3 -lTPhashmap -Wl,-rpath,. -L. -o tphashmap_user_test tphashmap_user_test.c
