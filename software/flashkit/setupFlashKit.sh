# Setup FlashKit
if [ ! -d "FlashKit" ]; then
	git clone git@github.com:akashdhruv/FlashKit --branch main FlashKit && cd FlashKit

	# checkout desired branch
	git checkout 364c99d
else
	cd FlashKit
fi

# install in development mode
module load python/3.8.0
source /pub/sheikhh1/envs/flashx/bin/activate
python3 setup.py develop
