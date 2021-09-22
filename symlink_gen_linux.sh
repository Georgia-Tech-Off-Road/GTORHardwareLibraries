find . -maxdepth 1 -mindepth 1 -type d \
		-not -path "./ExternalLibraries" \
		-not -path "./Sensors" \
		-exec ln -sf $PWD/'{}' ~/Arduino/libraries/'{}' \;

cd ExternalLibraries
find . -maxdepth 1 -mindepth 1 -type d \
		-exec ln -sf $PWD/'{}' ~/Arduino/libraries/'{}' \;
		
cd ../Sensors
find . -maxdepth 1 -mindepth 1 -type d \
		-exec ln -sf $PWD/'{}' ~/Arduino/libraries/'{}' \;
