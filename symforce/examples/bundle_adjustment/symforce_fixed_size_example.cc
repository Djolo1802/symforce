#include <iostream>

#include <sym/pose3.h>
#include <symforce/opt/assert.h>
#include <symforce/opt/optimizer.h>

#include "./build_example_state.h"
#include "symforce/bundle_adjustment_example/linearization.h"

namespace sym {

static constexpr int kPoseDim = 6;
static constexpr int kVariablesDim = kNumLandmarks + (kNumViews - 1) * kPoseDim;
static constexpr int kNumReprojectionErrors = kNumLandmarks * (kNumViews - 1);
static constexpr int kResidualDim = 2 * kNumReprojectionErrors                // Reprojection error
                                    + kNumViews * (kNumViews - 1) * kPoseDim  // Pose prior
                                    + kNumLandmarks;                          // Inverse range prior

sym::Factord BuildFactor() {
  const std::vector<sym::Key> factor_keys = {{Var::CALIBRATION, 0},
                                             {Var::VIEW, 0},
                                             {Var::CALIBRATION, 1},
                                             {Var::VIEW, 1},
                                             {Var::POSE_PRIOR_R, 0, 0},
                                             {Var::POSE_PRIOR_T, 0, 0},
                                             {Var::POSE_PRIOR_WEIGHT, 0, 0},
                                             {Var::POSE_PRIOR_SIGMAS, 0, 0},
                                             {Var::POSE_PRIOR_R, 0, 1},
                                             {Var::POSE_PRIOR_T, 0, 1},
                                             {Var::POSE_PRIOR_WEIGHT, 0, 1},
                                             {Var::POSE_PRIOR_SIGMAS, 0, 1},
                                             {Var::POSE_PRIOR_R, 1, 0},
                                             {Var::POSE_PRIOR_T, 1, 0},
                                             {Var::POSE_PRIOR_WEIGHT, 1, 0},
                                             {Var::POSE_PRIOR_SIGMAS, 1, 0},
                                             {Var::POSE_PRIOR_R, 1, 1},
                                             {Var::POSE_PRIOR_T, 1, 1},
                                             {Var::POSE_PRIOR_WEIGHT, 1, 1},
                                             {Var::POSE_PRIOR_SIGMAS, 1, 1},
                                             {Var::MATCH_SOURCE_COORDS, 1, 0},
                                             {Var::MATCH_TARGET_COORDS, 1, 0},
                                             {Var::MATCH_WEIGHT, 1, 0},
                                             {Var::LANDMARK_PRIOR, 1, 0},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 0},
                                             {Var::MATCH_SOURCE_COORDS, 1, 1},
                                             {Var::MATCH_TARGET_COORDS, 1, 1},
                                             {Var::MATCH_WEIGHT, 1, 1},
                                             {Var::LANDMARK_PRIOR, 1, 1},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 1},
                                             {Var::MATCH_SOURCE_COORDS, 1, 2},
                                             {Var::MATCH_TARGET_COORDS, 1, 2},
                                             {Var::MATCH_WEIGHT, 1, 2},
                                             {Var::LANDMARK_PRIOR, 1, 2},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 2},
                                             {Var::MATCH_SOURCE_COORDS, 1, 3},
                                             {Var::MATCH_TARGET_COORDS, 1, 3},
                                             {Var::MATCH_WEIGHT, 1, 3},
                                             {Var::LANDMARK_PRIOR, 1, 3},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 3},
                                             {Var::MATCH_SOURCE_COORDS, 1, 4},
                                             {Var::MATCH_TARGET_COORDS, 1, 4},
                                             {Var::MATCH_WEIGHT, 1, 4},
                                             {Var::LANDMARK_PRIOR, 1, 4},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 4},
                                             {Var::MATCH_SOURCE_COORDS, 1, 5},
                                             {Var::MATCH_TARGET_COORDS, 1, 5},
                                             {Var::MATCH_WEIGHT, 1, 5},
                                             {Var::LANDMARK_PRIOR, 1, 5},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 5},
                                             {Var::MATCH_SOURCE_COORDS, 1, 6},
                                             {Var::MATCH_TARGET_COORDS, 1, 6},
                                             {Var::MATCH_WEIGHT, 1, 6},
                                             {Var::LANDMARK_PRIOR, 1, 6},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 6},
                                             {Var::MATCH_SOURCE_COORDS, 1, 7},
                                             {Var::MATCH_TARGET_COORDS, 1, 7},
                                             {Var::MATCH_WEIGHT, 1, 7},
                                             {Var::LANDMARK_PRIOR, 1, 7},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 7},
                                             {Var::MATCH_SOURCE_COORDS, 1, 8},
                                             {Var::MATCH_TARGET_COORDS, 1, 8},
                                             {Var::MATCH_WEIGHT, 1, 8},
                                             {Var::LANDMARK_PRIOR, 1, 8},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 8},
                                             {Var::MATCH_SOURCE_COORDS, 1, 9},
                                             {Var::MATCH_TARGET_COORDS, 1, 9},
                                             {Var::MATCH_WEIGHT, 1, 9},
                                             {Var::LANDMARK_PRIOR, 1, 9},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 9},
                                             {Var::MATCH_SOURCE_COORDS, 1, 10},
                                             {Var::MATCH_TARGET_COORDS, 1, 10},
                                             {Var::MATCH_WEIGHT, 1, 10},
                                             {Var::LANDMARK_PRIOR, 1, 10},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 10},
                                             {Var::MATCH_SOURCE_COORDS, 1, 11},
                                             {Var::MATCH_TARGET_COORDS, 1, 11},
                                             {Var::MATCH_WEIGHT, 1, 11},
                                             {Var::LANDMARK_PRIOR, 1, 11},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 11},
                                             {Var::MATCH_SOURCE_COORDS, 1, 12},
                                             {Var::MATCH_TARGET_COORDS, 1, 12},
                                             {Var::MATCH_WEIGHT, 1, 12},
                                             {Var::LANDMARK_PRIOR, 1, 12},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 12},
                                             {Var::MATCH_SOURCE_COORDS, 1, 13},
                                             {Var::MATCH_TARGET_COORDS, 1, 13},
                                             {Var::MATCH_WEIGHT, 1, 13},
                                             {Var::LANDMARK_PRIOR, 1, 13},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 13},
                                             {Var::MATCH_SOURCE_COORDS, 1, 14},
                                             {Var::MATCH_TARGET_COORDS, 1, 14},
                                             {Var::MATCH_WEIGHT, 1, 14},
                                             {Var::LANDMARK_PRIOR, 1, 14},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 14},
                                             {Var::MATCH_SOURCE_COORDS, 1, 15},
                                             {Var::MATCH_TARGET_COORDS, 1, 15},
                                             {Var::MATCH_WEIGHT, 1, 15},
                                             {Var::LANDMARK_PRIOR, 1, 15},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 15},
                                             {Var::MATCH_SOURCE_COORDS, 1, 16},
                                             {Var::MATCH_TARGET_COORDS, 1, 16},
                                             {Var::MATCH_WEIGHT, 1, 16},
                                             {Var::LANDMARK_PRIOR, 1, 16},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 16},
                                             {Var::MATCH_SOURCE_COORDS, 1, 17},
                                             {Var::MATCH_TARGET_COORDS, 1, 17},
                                             {Var::MATCH_WEIGHT, 1, 17},
                                             {Var::LANDMARK_PRIOR, 1, 17},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 17},
                                             {Var::MATCH_SOURCE_COORDS, 1, 18},
                                             {Var::MATCH_TARGET_COORDS, 1, 18},
                                             {Var::MATCH_WEIGHT, 1, 18},
                                             {Var::LANDMARK_PRIOR, 1, 18},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 18},
                                             {Var::MATCH_SOURCE_COORDS, 1, 19},
                                             {Var::MATCH_TARGET_COORDS, 1, 19},
                                             {Var::MATCH_WEIGHT, 1, 19},
                                             {Var::LANDMARK_PRIOR, 1, 19},
                                             {Var::LANDMARK_PRIOR_SIGMA, 1, 19},
                                             {Var::LANDMARK, 0},
                                             {Var::LANDMARK, 1},
                                             {Var::LANDMARK, 2},
                                             {Var::LANDMARK, 3},
                                             {Var::LANDMARK, 4},
                                             {Var::LANDMARK, 5},
                                             {Var::LANDMARK, 6},
                                             {Var::LANDMARK, 7},
                                             {Var::LANDMARK, 8},
                                             {Var::LANDMARK, 9},
                                             {Var::LANDMARK, 10},
                                             {Var::LANDMARK, 11},
                                             {Var::LANDMARK, 12},
                                             {Var::LANDMARK, 13},
                                             {Var::LANDMARK, 14},
                                             {Var::LANDMARK, 15},
                                             {Var::LANDMARK, 16},
                                             {Var::LANDMARK, 17},
                                             {Var::LANDMARK, 18},
                                             {Var::LANDMARK, 19},
                                             {Var::EPSILON},
                                             {Var::GNC_SCALE},
                                             {Var::GNC_MU}};

  const std::vector<sym::Key> optimized_keys = {
      {Var::VIEW, 1},      {Var::LANDMARK, 0},  {Var::LANDMARK, 1},  {Var::LANDMARK, 2},
      {Var::LANDMARK, 3},  {Var::LANDMARK, 4},  {Var::LANDMARK, 5},  {Var::LANDMARK, 6},
      {Var::LANDMARK, 7},  {Var::LANDMARK, 8},  {Var::LANDMARK, 9},  {Var::LANDMARK, 10},
      {Var::LANDMARK, 11}, {Var::LANDMARK, 12}, {Var::LANDMARK, 13}, {Var::LANDMARK, 14},
      {Var::LANDMARK, 15}, {Var::LANDMARK, 16}, {Var::LANDMARK, 17}, {Var::LANDMARK, 18},
      {Var::LANDMARK, 19}};

  return sym::Factord::Hessian(bundle_adjustment_example::Linearization<double>, factor_keys,
                               optimized_keys);
}

void RunFixedBundleAdjustment() {
  // Create initial state
  std::mt19937 gen(42);
  Valuesd values = BuildValues(gen, kNumLandmarks);

  std::cout << "Initial State:" << std::endl;
  for (int i = 0; i < kNumViews; i++) {
    std::cout << "Pose " << i << ": " << sym::Pose3d(values.At<sym::Pose3d>({Var::VIEW, i}))
              << std::endl;
  }
  std::cout << "Landmarks: ";
  for (int i = 0; i < kNumLandmarks; i++) {
    std::cout << values.At<double>({Var::LANDMARK, i}) << " ";
  }
  std::cout << std::endl;

  // Create and set up Optimizer
  const optimizer_params_t optimizer_params = OptimizerParams();

  Optimizerd optimizer(optimizer_params, {BuildFactor()}, kEpsilon, {}, "sym::Optimizer");

  optimizer.Optimize(&values);

  // Print out results
  std::cout << "Optimized State:" << std::endl;
  for (int i = 0; i < kNumViews; i++) {
    std::cout << "Pose " << i << ": " << sym::Pose3d(values.At<sym::Pose3d>({Var::VIEW, i}))
              << std::endl;
  }
  std::cout << "Landmarks: ";
  for (int i = 0; i < kNumLandmarks; i++) {
    std::cout << values.At<double>({Var::LANDMARK, i}) << " ";
  }
  std::cout << std::endl;

  const auto& iteration_stats = optimizer.Stats().iterations;
  const auto& first_iter = iteration_stats[0];
  const auto& last_iter = iteration_stats[iteration_stats.size() - 1];
  std::cout << "Iterations: " << last_iter.iteration << std::endl;
  std::cout << "Lambda: " << last_iter.current_lambda << std::endl;
  std::cout << "Initial error: " << first_iter.new_error << std::endl;
  std::cout << "Final error: " << last_iter.new_error << std::endl;

  // Check successful convergence
  SYM_ASSERT(last_iter.iteration == 5);
  SYM_ASSERT(last_iter.new_error < 3);
}

}  // namespace sym
