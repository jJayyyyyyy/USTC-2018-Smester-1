function plotboundary(labels, features, model, varargin)

% PLOTBOUNDARY    Plot the SVM classification boundary in Exercise 8
%
%   plotboundary(labels, features, model, fill_on) plots the training data
%   and decision boundary, given a model produced by LIBSVM
%    
%   The parameter 'fill_on' is a boolean that indicates whether a filled-in
%   contour map should be produced.

figure; hold on

% Make classification predictions over a grid of values
xplot = linspace(min(features(:,1)), max(features(:,1)), 100)';
yplot = linspace(min(features(:,2)), max(features(:,2)), 100)';
[X, Y] = meshgrid(xplot, yplot);
vals = zeros(size(X));
for i = 1:size(X, 2)
   x = [X(:,i),Y(:,i)];
   % Need to use evalc here to suppress LIBSVM accuracy printouts
   [T,predicted_labels, accuracy, decision_values] = ...
       evalc('svmpredict(ones(size(x(:,1))), x, model)');
   clear T;
   vals(:,i) = decision_values;
end

% Plot the SVM boundary
colormap bone
if (size(varargin, 2) == 1) && (varargin{1} == 't')
    contourf(X,Y, vals, 50, 'LineStyle', 'none');
end
contour(X,Y, vals, [0 0], 'LineWidth', 2, 'Color', 'k');

% Plot the training data on top of the boundary
pos = find(labels == 1);
neg = find(labels == -1);
plot(features(pos,1), features(pos,2), 'ko', 'MarkerFaceColor', 'r'); hold on;
plot(features(neg,1), features(neg,2), 'ko', 'MarkerFaceColor', 'g')
