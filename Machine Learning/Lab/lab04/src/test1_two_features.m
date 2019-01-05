% https://github.com/DishantK1807/Machine-Learning-Algorithms-Andrew-Ng./blob/master/SVM-Linear-Classification/TwoFeature_SVMClassification.m

[y, x] = libsvmread('dataset/ex7Data/twofeature.txt');

% Setting the cost
% C = 100;
C = 1

% Training the model and get the primal variables w, b from the model

% Libsvm options
% -s 0 : classification
% -t 0 : linear kernel
% -c somenumber : set the cost
model = svmtrain(y, x, sprintf('-s 0 -t 0 -c %g', C));
w = model.SVs' * model.sv_coef;
b = -model.rho;

if (model.Label(1) == -1)
    w = -w; b = -b;
end


% Ploting the data points
figure
pos = find(y == 1);
neg = find(y == -1);
plot(x(pos,1), x(pos,2), 'ko', 'MarkerFaceColor', 'b'); hold on;
plot(x(neg,1), x(neg,2), 'ko', 'MarkerFaceColor', 'g')

% Plotting the decision boundary
plot_x = linspace(min(x(:,1)), max(x(:,1)), 30);
plot_y = (-1/w(2))*(w(1)*plot_x + b);
plot(plot_x, plot_y, 'k-', 'LineWidth', 2)

title(sprintf('SVM Linear Classifier with C = %g', C), 'FontSize', 14)

