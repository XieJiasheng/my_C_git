#############################################
# test env set here
# global
export XAVIER_LIB_PATH=/usr/lib
export XAVIER_BASE_LIB=libxavier-base.so

XAVIER_PRJ_PATH=$(cd $(dirname ${BASH_SOURCE[0]}); pwd )
echo "project path is $XAVIER_PRJ_PATH"
APP_PATH=/opt/seeing/app
export PYTHONPATH=$XAVIER_PRJ_PATH:$APP_PATH/packages
#############################################
