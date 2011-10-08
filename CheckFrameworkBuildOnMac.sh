#!/bin/sh

#
# This script is used to check the progress of Framework build on Mac.
# A file which names FRAME_CI_Build_Finished will be touched in a
# shared folder, which is defined by $WORKSPACE.  The script will exit
# the while-loop once the flag file is detected.
#

# Exit code
EXIT_FAILED=-1
EXIT_SUCCESS=0

#Check environment variables
if [ -z "$FRAMEWORK_CI_SHARED_FOLDER" ]; then
    echo "Environment variable: FRAMEWORK_CI_SHARED_FOLDER must be set"
    exit $EXIT_FAILED
fi

if [ ! -d "$FRAMEWORK_CI_SHARED_FOLDER" ]; then
    echo "$FRAMEWORK_CI_SHARED_FOLDER is not valid folder"
    exit $EXIT_FAILED
fi

WORKSPACE=$FRAMEWORK_CI_SHARED_FOLDER
BUILD_JOB_FINISHED_FLAG="Framework_CI_Build_Finished"

TIMEOUT=$((30 * 60))
counter=0

# Wait until build job is finished
echo "Waiting until build job is finished"
echo "Waiting..."
while [ 1 ]
do
    if [ -f $WORKSPACE/$BUILD_JOB_FINISHED_FLAG ]; then
        exit $EXIT_SUCCESS
    else
        sleep 5
        counter=$(($counter + 1))
        TimeElapsed=$(($counter * 5))
        if [ $TimeElapsed -gt $TIMEOUT ]; then
            echo "time out to wait build job on Mac."
            echo "Stop waiting and return failed..."
            exit $EXIT_FAILED
        fi
    fi
done
