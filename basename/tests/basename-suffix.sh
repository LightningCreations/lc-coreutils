
if [ "$($1 $0 .sh)" -ne "basename-suffix" ]
then
exit 1
fi
