# DVO_SLAM_with_SE_Sync

## Description of the Project
SE-Sync, proposed by D. Rosen[1], is claimed to provide certifiably globally optimial sulutions for synchronization over Special Eucliden Group, which can be used in the pose-graph optimization of SLAM systems. We want to investigate its performance over g2o[2], a widely used library for graph optimization, on SLAM tasks.  

Our work is based on DVO SLAM[3], a SLAM system that originally utilizes g2o library in its back-end pose-graph optimization. We replace g2o codes with SE-Sync, evaluate the performance of modified DVO SLAM on some sequences in TUM dataset[4], and do a comparison with the results of original DVO SLAM. Our work is summarized in the following section. 

## Implementation 
In DVO SLAM, g2o works in three places: 1) The first one is the optimization of a newly got local graph before it's inserted into the global graph. 2) After that, DVO SLAM try establishing loop closure constraints between keyframes, and perform g2o optimization on the global graph if new constraints are set up. If any outlier constraint is detected, it would be removed and the global graph would be optimized again by g2o. 3) When SLAM process ends, global graph optimization by g2o and outlier constraints detection like what is done in step 2) are performed iteratively and end when either no outlier constraint is detected or 10 iterations are performed. 

Thus in our experiment, we try several ways to incorperate SE-Sync into DVO SLAM, the optimization performances of which are shown in the table below. Besides, we also evaluate the how runtime of SE-Sync varies as the size of graph grows. The performance of  original g2o optimization is also included for comparison.

## Comparison Results
### optimization
RMSE of absolute trajectory error on some TUM sequences are shown here for evaluation. 

```
implementation	(1)		(2)		(3)		(4)		(5)		(6)		(7)		(8)

fr1_360		0.091643	0.231445	0.094439	0.071950	0.095184	0.095479	0.110079	0.104853
fr1_desk	0.022747	0.021713	0.022802	0.022565	0.021726	0.021726	0.021765	0.021972
fr1_desk2	0.027864	0.028452	0.028676	0.026995	0.029616	0.030655	0.029381	0.028833
fr1_plant	0.030187	0.029949	0.030117	0.031065	0.029377	0.028414	0.028350	0.030798
fr1_room	0.081622	0.071230	0.080350	0.071358	0.074496	0.073656	0.074333	0.071186
fr1_rpy		0.023377	0.021999	0.023494	0.021920	0.022046	0.021947	0.024542	0.022506
fr1_teddy	0.039596	0.048779	0.038841	0.048249	0.047388	0.047900	0.052620	0.050110
fr1_xyz		0.012997	0.012631	0.012984	0.012605	0.012997	0.012527	0.013254	0.012548
fr2_desk	0.078666	0.067789	0.078979	0.065512	0.067410	0.065490	0.070938	0.067138
fr2_dishes	0.052436	0.623265	0.051506	0.052474	0.051997	0.052141	0.054243	0.053548
fr3_long_o	0.022960	0.025396	0.025765	0.026022	0.026432	0.024961	0.025914	0.026080

mean		0.044009	0.107513	0.044359	0.040974	0.043515	0.043172	0.045947	0.044506
```

		
(1):original g2o optimization
(2):replace all g2o with SE-Sync, add SE-Sync after step 3)
(3):replace g2o with SE-Sync in step 1) 
(4):replace g2o with SE-Sync in step 1) and 2), add SE-Sync after step 3)
(5):only add SE-Sync after step 3)
(6):replace g2o with SE-Sync in step 1), add SE-Sync after step 3)
(7):replace all global SE-Sync in (4) with global SE-Sync on keyframes
(8):replace all global SE-Sync but that after step 3) in (4) with global SE-Sync on keyframes
