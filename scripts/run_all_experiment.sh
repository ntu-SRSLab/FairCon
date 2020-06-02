#!/bin/bash

#execute the auction
auction=/home/fairness/contracts/experiment/auction
echo "run experiment under /home/fairness/contracts/experiment/auction"
truth=$auction/truthful
collusion=$auction/collusion
optimal=$auction/optimal
efficient=$auction/efficient
for file in $(ls $truth)
do
	mkdir -p $truth/log
	faircon -symexe-main $truth/$file 2>&1 >$truth/log/$file 
done

for file in $(ls $collusion)
do
	mkdir -p $collusion/log
	faircon -symexe-main $collusion/$file 2>&1 >$collusion/log/$file 
done

for file in $(ls $optimal)
do
	mkdir -p $optimal/log
	faircon -symexe-main $optimal/$file 2>&1 >$optimal/log/$file 
done

for file in $(ls $efficient)
do
	mkdir -p $efficient/log
	faircon -symexe-main $efficient/$file 2>&1 >$efficient/log/$file 
done

#excute the performance
performance=/home/fairness/contracts/experiment/performance
truth=$performance/truthful
collusion=$performance/collusion
optimal=$performance/optimal
efficient=$performance/efficient
for file in $(ls $truth)
do
	mkdir -p $truth/log
	faircon -symexe-main $truth/$file 2>&1 >$truth/log/$file 
done
for file in $(ls $collusion)
do
	mkdir -p $collusion/log
	faircon -symexe-main $collusion/$file 2>&1 >$collusion/log/$file 
done

for file in $(ls $optimal)
do
      mkdir -p $optimal/log
	faircon -symexe-main $optimal/$file 2>&1 >$optimal/log/$file 
done

for file in $(ls $efficient)
do
      mkdir -p $efficient/log
	faircon -symexe-main $efficient/$file 2>&1 >$efficient/log/$file 
done


#execute the voting
voting=/home/fairness/contracts/experiment/voting
truth=$voting/truthful
collusion=$voting/collusion
efficient=$voting/efficient
for file in $(ls $truth)
do
	mkdir -p $truth/log
	faircon -symexe-main $truth/$file 2>&1 >$truth/log/$file 
done
for file in $(ls $collusion)
do
	mkdir -p $optimal/log
	mkdir -p $collusion/log
	faircon -symexe-main $collusion/$file 2>&1 >$collusion/log/$file 
done
for file in $(ls $efficient)
do
	mkdir -p $efficient/log
	faircon -symexe-main $efficient/$file 2>&1 >$efficient/log/$file 
done

#execute the voting
voting=/home/fairness/contracts/experiment/voting-0-1
truth=$voting/truthful
collusion=$voting/collusion
efficient=$voting/efficient
for file in $(ls $truth)
do
	mkdir -p $truth/log
	faircon -symexe-main $truth/$file 2>&1 >$truth/log/$file 
done
for file in $(ls $collusion)
do
	mkdir -p $collusion/log
	faircon -symexe-main $collusion/$file 2>&1 >$collusion/log/$file 
done
for file in $(ls $efficient)
do
	mkdir -p $efficient/log
	faircon -symexe-main $efficient/$file 2>&1 >$efficient/log/$file 
done

echo "done"
echo "check log under /home/fairness/contracts/experiment/*/**/log/"