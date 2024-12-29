```cpp
KalmanFilter KF(stateNum, measureNum, 0);
//Mat processNoise(stateNum, 1, CV_32F);
Mat measurement = Mat::zeros(measureNum,1, CV_32F);


//A 状态转移矩阵
KF.transitionMatrix = (Mat_<float>(stateNum, stateNum) << 
    1, 0, 1, 0,
    0, 1, 0, 1,
    0, 0, 1, 0,
    0, 0, 0, 1);


//这里没有设置控制矩阵B，默认为零

/*
观测矩阵H
    1,0,0,0
    0,1,0,0
*/
setIdentity(KF.measurementMatrix);                      
setIdentity(KF.processNoiseCov, Scalar::all(1e-4));     //Q高斯白噪声，单位阵
setIdentity(KF.measurementNoiseCov, Scalar::all(1e-2)); //R高斯白噪声，单位阵
setIdentity(KF.errorCovPost, Scalar::all(1e-1));        //P后验误差估计协方差矩阵，初始化为单位阵
randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));  //初始化状态为随机值


Mat prediction = KF.predict();
Point predict_pt = Point((int)prediction.at<float>(0), (int)prediction.at<float>(1));

measurement.at<float>(0) = (float)center_x;
measurement.at<float>(1) = (float)center_y;
KF.correct(measurement);

center_x = (int)prediction.at<float>(0);
center_y = (int)prediction.at<float>(1);

```