#!/bin/bash

#execute the auction
auction=/home/fairness/contracts/experiment/auction
truth=$auction/truthful
collusion=$auction/collusion
optimal=$auction/optimal
efficient=$auction/efficient
mkdir -p $truth/log
mkdir -p $collusion/log
mkdir -p $optimal/log
mkdir -p $efficient/log
for file in $(ls $truth)
do
	faircon -symexe-main $truth/$file 2>&1 >$truth/log/$file 
done

for file in $(ls $collusion)
do
	faircon -symexe-main $collusion/$file 2>&1 >$collusion/log/$file 
done

for file in $(ls $optimal)
do
	faircon -symexe-main $optimal/$file 2>&1 >$optimal/log/$file 
done

for file in $(ls $efficient)
do
	faircon -symexe-main $efficient/$file 2>&1 >$efficient/log/$file 
done

#excute the performance
performance=/home/fairness/contracts/experiment/performance
truth=$performance/truthful
collusion=$performance/collusion
optimal=$performance/optimal
efficient=$performance/efficient
mkdir -p $truth/log
mkdir -p $collusion/log
mkdir -p $optimal/log
mkdir -p $efficient/log
for file in $(ls $truth)
do
	faircon -symexe-main $truth/$file 2>&1 >$truth/log/$file 
done
for file in $(ls $collusion)
do
	faircon -symexe-main $collusion/$file 2>&1 >$collusion/log/$file 
done

for file in $(ls $optimal)
do
	faircon -symexe-main $optimal/$file 2>&1 >$optimal/log/$file 
done

for file in $(ls $efficient)
do
	faircon -symexe-main $efficient/$file 2>&1 >$efficient/log/$file 
done


#execute the voting
voting=/home/fairness/contracts/experiment/voting
truth=$voting/truthful
collusion=$voting/collusion
optimal=$voting/optimal
efficient=$voting/efficient
mkdir -p $truth/log
mkdir -p $collusion/log
mkdir -p $optimal/log
mkdir -p $efficient/log
for file in $(ls $truth)
do
	faircon -symexe-main $truth/$file 2>&1 >$truth/log/$file 
done
for file in $(ls $collusion)
do
	faircon -symexe-main $collusion/$file 2>&1 >$collusion/log/$file 
done

for file in $(ls $optimal)
do
	faircon -symexe-main $optimal/$file 2>&1 >$optimal/log/$file 
done

for file in $(ls $efficient)
do
	faircon -symexe-main $efficient/$file 2>&1 >$efficient/log/$file 
done

#execute the voting
voting=/home/fairness/contracts/experiment/voting-0-1
truth=$voting/truthful
collusion=$voting/collusion
optimal=$voting/optimal
efficient=$voting/efficient
mkdir -p $truth/log
mkdir -p $collusion/log
mkdir -p $optimal/log
mkdir -p $efficient/log
for file in $(ls $truth)
do
	faircon -symexe-main $truth/$file 2>&1 >$truth/log/$file 
done
for file in $(ls $collusion)
do
	faircon -symexe-main $collusion/$file 2>&1 >$collusion/log/$file 
done

for file in $(ls $optimal)
do
	faircon -symexe-main $optimal/$file 2>&1 >$optimal/log/$file 
done

for file in $(ls $efficient)
do
	faircon -symexe-main $efficient/$file 2>&1 >$efficient/log/$file 
done

