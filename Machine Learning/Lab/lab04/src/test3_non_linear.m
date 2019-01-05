clear all; close all; clc;

% Load training features and labels
[y, x] = libsvmread('dataset/ex8Data/ex8a.txt');

% gamma = 1;
% gamma = 10;
gamma = 100;

% Libsvm options 参数
% -s 0 : classification
% -t 2 : RBF kernel
% -g : gamma in the RBF kernel
model = svmtrain(y, x, sprintf('-s 0 -t 2 -g %g', gamma));

% Display training accuracy
[predicted_label, accuracy, decision_values] = svmpredict(y, x, model);

% Plot training data and decision boundary
% plotboundary(y, x, model);
plotboundary(y, x, model);

title(sprintf('\\gamma = %g', gamma), 'FontSize', 14);
