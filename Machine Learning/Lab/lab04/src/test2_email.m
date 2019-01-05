% https://github.com/DishantK1807/Machine-Learning-Algorithms-Andrew-Ng./blob/master/SVM-Linear-Classification/EmailText_SVMClassification.m


% SVM Email text classification
% Load training features and labels
[train_y, train_x] = libsvmread('dataset/ex7Data/email_train-100.txt');

% Train the model and get the primal variables w, b from the model

% Libsvm options
% -t 0 : linear kernel
% Leaving other options as their defaults 
model = svmtrain(train_y, train_x, '-s 0 -t 0');

w = model.SVs' * model.sv_coef;
b = -model.rho;

if (model.Label(1) == -1)
    w = -w; b = -b;
end

% Loading testing features and labels
[test_y, test_x] = libsvmread('dataset/ex7Data/email_test.txt');

[predicted_label, accuracy, decision_values] = svmpredict(test_y, test_x, model);
% After running svmpredict, the accuracy is printed in console



% plotboundary(test_y, test_x, model)

% Ploting the data points
figure
pos = find(test_y == 1);
neg = find(test_y == -1);
plot(test_x(pos,1), test_x(pos,2), 'ko', 'MarkerFaceColor', 'b'); hold on;
plot(test_x(neg,1), test_x(neg,2), 'ko', 'MarkerFaceColor', 'g')

% Plotting the decision boundary
plot_x = linspace(min(test_x(:,1)), max(test_x(:,1)), 30);
plot_y = (-1/w(2))*(w(1)*plot_x + b);
plot(plot_x, plot_y, 'k-', 'LineWidth', 2)

% title(sprintf('SVM Linear Classifier with C = %g', C), 'FontSize', 14)

