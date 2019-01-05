% https://github.com/DishantK1807/Machine-Learning-Algorithms-Andrew-Ng./blob/master/SVM-Linear-Classification/TwoFeature_SVMClassification.m

[y, x] = libsvmread('dataset/iris_train.txt');

% Setting the cost
C = 100;
% C = 1

% Training the model and get the primal variables w, b from the model
model = svmtrain(y, x, sprintf('-s 0 -t 2 -c 1 -g 0.1'));
w = model.SVs' * model.sv_coef;
b = -model.rho;

if model.Label(1) == -1
  w = -w;
  b = -b;
end

[test_y, test_x] = libsvmread('dataset/iris_test.txt');

[predicted_label, accuracy, decision_values] = svmpredict(test_y, test_x, model);
% After running svmpredict, the accuracy is printed in console


% Ploting the data points
% figure
% pos1 = find(test_y == 1);
% pos2 = find(test_y == 2);
% pos3 = find(test_y == 3);
% plot(x(pos1,1), x(pos1,2), 'ko', 'MarkerFaceColor', 'b'); hold on;
% plot(x(pos2,1), x(pos2,2), 'ko', 'MarkerFaceColor', 'g'); hold on;
% plot(x(pos3,1), x(pos3,2), 'ko', 'MarkerFaceColor', 'r')

% % % Plotting the decision boundary
% plot_x = linspace(min(x(:,1)), max(x(:,1)), 30);
% plot_y = (-1/w(2))*(w(1)*plot_x + b);
% plot(plot_x, plot_y, 'k-', 'LineWidth', 2)

% title(sprintf('SVM Linear Classifier with C = %g', C), 'FontSize', 14)




% -s svm_type : set type of SVM (default 0)
% 	0 -- C-SVC		(multi-class classification)
% 	1 -- nu-SVC		(multi-class classification)
% 	2 -- one-class SVM
% 	3 -- epsilon-SVR	(regression)
% 	4 -- nu-SVR		(regression)
% -t kernel_type : set type of kernel function (default 2)
% 	0 -- linear: u'*v
% 	1 -- polynomial: (gamma*u'*v + coef0)^degree
% 	2 -- radial basis function: exp(-gamma*|u-v|^2)
% 	3 -- sigmoid: tanh(gamma*u'*v + coef0)
% 	4 -- precomputed kernel (kernel values in training_set_file)

% [y, x] = libsvmread('dataset/iris.txt');
% figure
% pos1 = find(y == 1);
% pos2 = find(y == 2);
% pos3 = find(y == 3);
% plot(x(pos1,1), x(pos1,2), 'ko', 'MarkerFaceColor', 'b'); hold on;
% plot(x(pos2,1), x(pos2,2), 'ko', 'MarkerFaceColor', 'g'); hold on;
% plot(x(pos3,1), x(pos3,2), 'ko', 'MarkerFaceColor', 'r')
