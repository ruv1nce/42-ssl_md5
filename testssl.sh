echo "ERROR MSGS"
echo "********************** ./test"
./test
echo "********************** ./test sdf"
./test sdf
echo "********************** ./test md5 -z"
./test md5 -z
echo "********************** ./test md5 -s"
./test md5 -s
echo "********************** ./test md5 -s one -s"
./test md5 -s one -s two -s
echo ""
echo "COMPARE TO MD5"
echo "********************** echo zero | (./test) md5"
echo zero | ./test md5
echo zero | md5
echo "********************** echo zero | (./test) md5 -p"
echo zero | ./test md5 -p
echo zero | md5 -p
echo "********************** (./test) md5 -s one -s two"
./test md5 -s one -s two
md5 -s one -s two
echo "********************** (./test) md5 testfile"
./test md5 testfile
md5 testfile
echo "********************** (./test) md5 -s one testfile"
./test md5 -s one testfile
md5 -s one testfile
echo ""
echo "COMPARE TO SHA256"
echo zero | ./test sha256
echo zero | shasum -a 256
echo "********************** (./test) sha256 testfile"
./test sha256 -r testfile
shasum -a 256 testfile
