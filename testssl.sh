echo "ERROR MSGS"
echo "********************** ./ft_ssl"
./ft_ssl
echo "********************** ./ft_ssl sdf"
./ft_ssl sdf
echo "********************** ./ft_ssl md5 -z"
./ft_ssl md5 -z
echo "********************** ./ft_ssl md5 -s"
./ft_ssl md5 -s
echo "********************** ./ft_ssl md5 -s one -s"
./ft_ssl md5 -s one -s two -s
echo ""
echo "COMPARE TO MD5"
echo "********************** echo zero | (./ft_ssl) md5"
echo zero | ./ft_ssl md5
echo zero | md5
echo "********************** echo zero | (./ft_ssl) md5 -p"
echo zero | ./ft_ssl md5 -p
echo zero | md5 -p
echo "********************** (./ft_ssl) md5 -s one -s two"
./ft_ssl md5 -s one -s two
md5 -s one -s two
echo "********************** (./ft_ssl) md5 testfile"
./ft_ssl md5 testfile
md5 testfile
echo "********************** (./ft_ssl) md5 -q testfile"
./ft_ssl md5 -q testfile
md5 -q testfile
echo "********************** (./ft_ssl) md5 -r -s one testfile"
./ft_ssl md5 -r -s one testfile
md5 -r -s one testfile
echo ""
echo "COMPARE TO SHA256"
echo "********************** echo zero | (./ft_ssl) sha256"
echo zero | ./ft_ssl sha256
echo zero | shasum -a 256
echo "********************** (./ft_ssl) sha256 testfile"
./ft_ssl sha256 -r testfile
shasum -a 256 testfile
echo ""
echo "COMPARE TO SHA224"
echo "********************** echo zero | (./ft_ssl) sha224"
echo zero | ./ft_ssl sha224
echo zero | shasum -a 224
echo "********************** (./ft_ssl) sha224 testfile"
./ft_ssl sha224 -r testfile
shasum -a 224 testfile
