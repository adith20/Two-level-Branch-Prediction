# Two-level-Branch-Prediction
This is a course project for Computer Architecture course at Purdue University, US. In this project, Two-level Branch Prediction is implemented using GAp and PAp schemes respectively. I have considered last 12-bits of the branch address and Branch History Register(BHR) of size 8-bits to index every entry of the Pattern History Table(PHT). 

In GAp scheme, the Branch History Register is global. In PAp scheme, the size of the Branch History table is 2^12 x 8. The size of the PHT in both cases is 2^12 x 2^8. Corresponding to every branch address and value of the BHR, an entry in PHT is referenced. Prediction is made based on the corresponding entry in the PHT. After prediction, based on the actual branch outcome, both the PHT and BHR is updated.

## Results
The Execution time for the GAp and PAp Prediction schemes are 9.6s and 10s respectively.
The Accuracy of Prediction for the **GAp predictor** is **93.94%** and that of **PAp predictor** is **92.54%**.
The Hardware cost for the GAp scheme is 256KB and for PAp scheme is 260KB.
