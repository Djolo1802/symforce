// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>

#include <sym/pose3.h>

namespace sym {

/**
 * Return the 2dof residual of reprojecting the landmark ray into the target spherical camera and
 * comparing it against the correspondence.
 *
 * The landmark is specified as a camera point in the source camera with an inverse range; this
 * means the landmark is fixed in the source camera and always has residual 0 there (this 0
 * residual is not returned, only the residual in the target camera is returned).
 *
 * The norm of the residual is whitened using the
 * :class:`BarronNoiseModel <symforce.opt.noise_models.BarronNoiseModel>`.  Whitening each
 * component of the reprojection error separately would result in rejecting individual components
 * as outliers. Instead, we minimize the whitened norm of the full reprojection error for each
 * point.  See
 * :meth:`ScalarNoiseModel.whiten_norm <symforce.opt.noise_models.ScalarNoiseModel.whiten_norm>`
 * for more information on this, and
 * :class:`BarronNoiseModel <symforce.opt.noise_models.BarronNoiseModel>` for more information on
 * the noise model.
 *
 * Args:
 *     source_pose: The pose of the source camera
 *     target_pose: The pose of the target camera
 *     target_calibration_storage: The storage vector of the target spherical camera calibration
 *     source_inverse_range: The inverse range of the landmark in the source camera
 *     p_camera_source: The location of the landmark in the source camera coordinate, will be
 *         normalized
 *     target_pixel: The location of the correspondence in the target camera
 *     weight: The weight of the factor
 *     gnc_mu: The mu convexity parameter for the
 *         :class:`BarronNoiseModel <symforce.opt.noise_models.BarronNoiseModel>`
 *     gnc_scale: The scale parameter for the
 *         :class:`BarronNoiseModel <symforce.opt.noise_models.BarronNoiseModel>`
 *     epsilon: Small positive value
 *     target_camera_model_class: The subclass of
 *         :class:`CameraCal <symforce.cam.camera_cal.CameraCal>` to use as the target camera model
 *
 * Outputs:
 *     res: 2dof whiten residual of the reprojection
 *     jacobian: (2x13) jacobian of res wrt args source_pose (6), target_pose (6),
 *               source_inverse_range (1)
 *     hessian: (13x13) Gauss-Newton hessian for args source_pose (6), target_pose (6),
 *              source_inverse_range (1)
 *     rhs: (13x1) Gauss-Newton rhs for args source_pose (6), target_pose (6), source_inverse_range
 *          (1)
 */
template <typename Scalar>
void InverseRangeLandmarkPolynomialReprojectionErrorFactor(
    const sym::Pose3<Scalar>& source_pose, const sym::Pose3<Scalar>& target_pose,
    const Eigen::Matrix<Scalar, 8, 1>& target_calibration_storage,
    const Scalar source_inverse_range, const Eigen::Matrix<Scalar, 3, 1>& p_camera_source,
    const Eigen::Matrix<Scalar, 2, 1>& target_pixel, const Scalar weight, const Scalar gnc_mu,
    const Scalar gnc_scale, const Scalar epsilon, Eigen::Matrix<Scalar, 2, 1>* const res = nullptr,
    Eigen::Matrix<Scalar, 2, 13>* const jacobian = nullptr,
    Eigen::Matrix<Scalar, 13, 13>* const hessian = nullptr,
    Eigen::Matrix<Scalar, 13, 1>* const rhs = nullptr) {
  // Total ops: 1126

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _source_pose = source_pose.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _target_pose = target_pose.Data();

  // Intermediate terms (297)
  const Scalar _tmp0 = std::pow(_target_pose[1], Scalar(2));
  const Scalar _tmp1 = -2 * _tmp0;
  const Scalar _tmp2 = std::pow(_target_pose[2], Scalar(2));
  const Scalar _tmp3 = 1 - 2 * _tmp2;
  const Scalar _tmp4 = _tmp1 + _tmp3;
  const Scalar _tmp5 = 2 * _source_pose[1];
  const Scalar _tmp6 = _source_pose[0] * _tmp5;
  const Scalar _tmp7 = 2 * _source_pose[2] * _source_pose[3];
  const Scalar _tmp8 = -_tmp7;
  const Scalar _tmp9 = _tmp6 + _tmp8;
  const Scalar _tmp10 = std::pow(Scalar(epsilon + std::pow(p_camera_source(0, 0), Scalar(2)) +
                                        std::pow(p_camera_source(1, 0), Scalar(2)) +
                                        std::pow(p_camera_source(2, 0), Scalar(2))),
                                 Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp11 = _tmp10 * p_camera_source(1, 0);
  const Scalar _tmp12 = 2 * _source_pose[0];
  const Scalar _tmp13 = _source_pose[2] * _tmp12;
  const Scalar _tmp14 = _source_pose[3] * _tmp5;
  const Scalar _tmp15 = _tmp13 + _tmp14;
  const Scalar _tmp16 = _tmp10 * p_camera_source(2, 0);
  const Scalar _tmp17 = std::pow(_source_pose[2], Scalar(2));
  const Scalar _tmp18 = -2 * _tmp17;
  const Scalar _tmp19 = std::pow(_source_pose[1], Scalar(2));
  const Scalar _tmp20 = -2 * _tmp19;
  const Scalar _tmp21 = _tmp10 * p_camera_source(0, 0);
  const Scalar _tmp22 = _source_pose[4] - _target_pose[4];
  const Scalar _tmp23 = _tmp11 * _tmp9 + _tmp15 * _tmp16 + _tmp21 * (_tmp18 + _tmp20 + 1) +
                        _tmp22 * source_inverse_range;
  const Scalar _tmp24 = 2 * _target_pose[2];
  const Scalar _tmp25 = _target_pose[0] * _tmp24;
  const Scalar _tmp26 = 2 * _target_pose[1];
  const Scalar _tmp27 = _target_pose[3] * _tmp26;
  const Scalar _tmp28 = -_tmp27;
  const Scalar _tmp29 = _tmp25 + _tmp28;
  const Scalar _tmp30 = _source_pose[3] * _tmp12;
  const Scalar _tmp31 = _source_pose[2] * _tmp5;
  const Scalar _tmp32 = _tmp10 * (_tmp30 + _tmp31);
  const Scalar _tmp33 = -_tmp14;
  const Scalar _tmp34 = _tmp13 + _tmp33;
  const Scalar _tmp35 = std::pow(_source_pose[0], Scalar(2));
  const Scalar _tmp36 = 1 - 2 * _tmp35;
  const Scalar _tmp37 = _source_pose[6] - _target_pose[6];
  const Scalar _tmp38 = _tmp16 * (_tmp20 + _tmp36) + _tmp21 * _tmp34 +
                        _tmp32 * p_camera_source(1, 0) + _tmp37 * source_inverse_range;
  const Scalar _tmp39 = _target_pose[3] * _tmp24;
  const Scalar _tmp40 = _target_pose[0] * _tmp26;
  const Scalar _tmp41 = _tmp39 + _tmp40;
  const Scalar _tmp42 = _tmp6 + _tmp7;
  const Scalar _tmp43 = -_tmp30;
  const Scalar _tmp44 = _tmp31 + _tmp43;
  const Scalar _tmp45 = _source_pose[5] - _target_pose[5];
  const Scalar _tmp46 = _tmp11 * (_tmp18 + _tmp36) + _tmp16 * _tmp44 + _tmp21 * _tmp42 +
                        _tmp45 * source_inverse_range;
  const Scalar _tmp47 = _tmp29 * _tmp38 + _tmp41 * _tmp46;
  const Scalar _tmp48 = _tmp23 * _tmp4 + _tmp47;
  const Scalar _tmp49 = std::pow(_target_pose[0], Scalar(2));
  const Scalar _tmp50 = -2 * _tmp49;
  const Scalar _tmp51 = _tmp1 + _tmp50 + 1;
  const Scalar _tmp52 = _target_pose[2] * _tmp26;
  const Scalar _tmp53 = 2 * _target_pose[0] * _target_pose[3];
  const Scalar _tmp54 = -_tmp53;
  const Scalar _tmp55 = _tmp52 + _tmp54;
  const Scalar _tmp56 = _tmp25 + _tmp27;
  const Scalar _tmp57 = _tmp23 * _tmp56 + _tmp46 * _tmp55;
  const Scalar _tmp58 = _tmp38 * _tmp51 + _tmp57;
  const Scalar _tmp59 = std::max<Scalar>(_tmp58, epsilon);
  const Scalar _tmp60 = Scalar(1.0) / (_tmp59);
  const Scalar _tmp61 = std::pow(_tmp59, Scalar(-2));
  const Scalar _tmp62 = _tmp3 + _tmp50;
  const Scalar _tmp63 = _tmp52 + _tmp53;
  const Scalar _tmp64 = -_tmp39;
  const Scalar _tmp65 = _tmp40 + _tmp64;
  const Scalar _tmp66 = _tmp23 * _tmp65 + _tmp38 * _tmp63;
  const Scalar _tmp67 = _tmp46 * _tmp62 + _tmp66;
  const Scalar _tmp68 = std::pow(_tmp67, Scalar(2));
  const Scalar _tmp69 = std::pow(_tmp48, Scalar(2));
  const Scalar _tmp70 = _tmp61 * _tmp68 + _tmp61 * _tmp69 + epsilon;
  const Scalar _tmp71 = std::pow(_tmp70, Scalar(2));
  const Scalar _tmp72 = Scalar(1.0) * target_calibration_storage(5, 0);
  const Scalar _tmp73 = Scalar(1.0) *
                            [&]() {
                              const Scalar base = _tmp70;
                              return base * base * base;
                            }() *
                            target_calibration_storage(7, 0) +
                        _tmp70 * _tmp72 + Scalar(1.0) * _tmp71 * target_calibration_storage(6, 0) +
                        Scalar(1.0);
  const Scalar _tmp74 = _tmp60 * _tmp73;
  const Scalar _tmp75 = _tmp74 * target_calibration_storage(0, 0);
  const Scalar _tmp76 = _tmp48 * _tmp75 + target_calibration_storage(2, 0) - target_pixel(0, 0);
  const Scalar _tmp77 = _tmp67 * target_calibration_storage(1, 0);
  const Scalar _tmp78 = _tmp74 * _tmp77 + target_calibration_storage(3, 0) - target_pixel(1, 0);
  const Scalar _tmp79 = std::pow(_tmp76, Scalar(2)) + std::pow(_tmp78, Scalar(2)) + epsilon;
  const Scalar _tmp80 = std::pow(_tmp79, Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp81 = std::sqrt(weight);
  const Scalar _tmp82 = Scalar(1.0) / (epsilon - gnc_mu + 1);
  const Scalar _tmp83 = epsilon + std::fabs(_tmp82);
  const Scalar _tmp84 = 2 - _tmp82;
  const Scalar _tmp85 =
      _tmp84 + epsilon * (2 * std::min<Scalar>(0, (((_tmp84) > 0) - ((_tmp84) < 0))) + 1);
  const Scalar _tmp86 = std::pow(gnc_scale, Scalar(-2));
  const Scalar _tmp87 = _tmp79 * _tmp86 / _tmp83 + 1;
  const Scalar _tmp88 = (Scalar(1) / Scalar(2)) * _tmp85;
  const Scalar _tmp89 =
      std::sqrt(Scalar(2)) * std::sqrt(Scalar(_tmp83 * (std::pow(_tmp87, _tmp88) - 1) / _tmp85));
  const Scalar _tmp90 = std::max<Scalar>(
      0, std::min<Scalar>((((_tmp58) > 0) - ((_tmp58) < 0)),
                          (((-std::sqrt(_tmp70) + target_calibration_storage(4, 0)) > 0) -
                           ((-std::sqrt(_tmp70) + target_calibration_storage(4, 0)) < 0))));
  const Scalar _tmp91 = _tmp81 * _tmp89 * _tmp90;
  const Scalar _tmp92 = _tmp80 * _tmp91;
  const Scalar _tmp93 = _tmp76 * _tmp92;
  const Scalar _tmp94 = _tmp78 * _tmp92;
  const Scalar _tmp95 = std::pow(_source_pose[3], Scalar(2));
  const Scalar _tmp96 = -_tmp95;
  const Scalar _tmp97 = -_tmp19;
  const Scalar _tmp98 = _tmp11 * _tmp44 + _tmp16 * (_tmp17 + _tmp35 + _tmp96 + _tmp97);
  const Scalar _tmp99 = -_tmp31;
  const Scalar _tmp100 = -_tmp35;
  const Scalar _tmp101 = _tmp100 + _tmp17;
  const Scalar _tmp102 = _tmp95 + _tmp97;
  const Scalar _tmp103 = _tmp11 * (_tmp101 + _tmp102) + _tmp16 * (_tmp43 + _tmp99);
  const Scalar _tmp104 = -_tmp6;
  const Scalar _tmp105 = _tmp11 * _tmp15 + _tmp16 * (_tmp104 + _tmp7);
  const Scalar _tmp106 = _tmp103 * _tmp51 + _tmp105 * _tmp56 + _tmp55 * _tmp98;
  const Scalar _tmp107 = (((_tmp58 - epsilon) > 0) - ((_tmp58 - epsilon) < 0)) + 1;
  const Scalar _tmp108 = _tmp107 / [&]() {
    const Scalar base = _tmp59;
    return base * base * base;
  }();
  const Scalar _tmp109 = _tmp108 * _tmp68;
  const Scalar _tmp110 = _tmp103 * _tmp63 + _tmp105 * _tmp65 + _tmp62 * _tmp98;
  const Scalar _tmp111 = 2 * _tmp61;
  const Scalar _tmp112 = _tmp111 * _tmp67;
  const Scalar _tmp113 = _tmp108 * _tmp69;
  const Scalar _tmp114 = _tmp103 * _tmp29 + _tmp105 * _tmp4 + _tmp41 * _tmp98;
  const Scalar _tmp115 = _tmp111 * _tmp48;
  const Scalar _tmp116 =
      -_tmp106 * _tmp109 - _tmp106 * _tmp113 + _tmp110 * _tmp112 + _tmp114 * _tmp115;
  const Scalar _tmp117 = Scalar(2.0) * _tmp70 * target_calibration_storage(6, 0);
  const Scalar _tmp118 = Scalar(3.0) * _tmp71 * target_calibration_storage(7, 0);
  const Scalar _tmp119 = _tmp116 * _tmp117 + _tmp116 * _tmp118 + _tmp116 * _tmp72;
  const Scalar _tmp120 = _tmp60 * _tmp77;
  const Scalar _tmp121 = _tmp74 * target_calibration_storage(1, 0);
  const Scalar _tmp122 = (Scalar(1) / Scalar(2)) * _tmp107 * _tmp61 * _tmp73;
  const Scalar _tmp123 = _tmp122 * _tmp77;
  const Scalar _tmp124 = -_tmp106 * _tmp123 + _tmp110 * _tmp121 + _tmp119 * _tmp120;
  const Scalar _tmp125 = 2 * _tmp78;
  const Scalar _tmp126 = _tmp48 * target_calibration_storage(0, 0);
  const Scalar _tmp127 = _tmp126 * _tmp60;
  const Scalar _tmp128 = _tmp122 * _tmp126;
  const Scalar _tmp129 = -_tmp106 * _tmp128 + _tmp114 * _tmp75 + _tmp119 * _tmp127;
  const Scalar _tmp130 = 2 * _tmp76;
  const Scalar _tmp131 = _tmp124 * _tmp125 + _tmp129 * _tmp130;
  const Scalar _tmp132 =
      _tmp80 * _tmp81 * _tmp86 * std::pow(_tmp87, Scalar(_tmp88 - 1)) * _tmp90 / _tmp89;
  const Scalar _tmp133 = (Scalar(1) / Scalar(2)) * _tmp132;
  const Scalar _tmp134 = _tmp133 * _tmp76;
  const Scalar _tmp135 = _tmp91 / (_tmp79 * std::sqrt(_tmp79));
  const Scalar _tmp136 = (Scalar(1) / Scalar(2)) * _tmp135;
  const Scalar _tmp137 = _tmp136 * _tmp76;
  const Scalar _tmp138 = _tmp129 * _tmp92 + _tmp131 * _tmp134 - _tmp131 * _tmp137;
  const Scalar _tmp139 = _tmp136 * _tmp78;
  const Scalar _tmp140 = _tmp133 * _tmp78;
  const Scalar _tmp141 = _tmp124 * _tmp92 - _tmp131 * _tmp139 + _tmp131 * _tmp140;
  const Scalar _tmp142 = -_tmp13;
  const Scalar _tmp143 = -_tmp17;
  const Scalar _tmp144 = _tmp143 + _tmp35;
  const Scalar _tmp145 = _tmp16 * (_tmp102 + _tmp144) + _tmp21 * (_tmp142 + _tmp33);
  const Scalar _tmp146 = _tmp19 + _tmp96;
  const Scalar _tmp147 = _tmp16 * _tmp34 + _tmp21 * (_tmp144 + _tmp146);
  const Scalar _tmp148 = _tmp16 * _tmp42 + _tmp21 * (_tmp30 + _tmp99);
  const Scalar _tmp149 = _tmp145 * _tmp4 + _tmp147 * _tmp29 + _tmp148 * _tmp41;
  const Scalar _tmp150 = _tmp145 * _tmp56 + _tmp147 * _tmp51 + _tmp148 * _tmp55;
  const Scalar _tmp151 = _tmp145 * _tmp65 + _tmp147 * _tmp63 + _tmp148 * _tmp62;
  const Scalar _tmp152 =
      -_tmp109 * _tmp150 + _tmp112 * _tmp151 - _tmp113 * _tmp150 + _tmp115 * _tmp149;
  const Scalar _tmp153 = _tmp117 * _tmp152 + _tmp118 * _tmp152 + _tmp152 * _tmp72;
  const Scalar _tmp154 = _tmp127 * _tmp153 - _tmp128 * _tmp150 + _tmp149 * _tmp75;
  const Scalar _tmp155 = _tmp120 * _tmp153 + _tmp121 * _tmp151 - _tmp123 * _tmp150;
  const Scalar _tmp156 = _tmp125 * _tmp155 + _tmp130 * _tmp154;
  const Scalar _tmp157 = _tmp134 * _tmp156 - _tmp137 * _tmp156 + _tmp154 * _tmp92;
  const Scalar _tmp158 = -_tmp139 * _tmp156 + _tmp140 * _tmp156 + _tmp155 * _tmp92;
  const Scalar _tmp159 = _tmp11 * (_tmp14 + _tmp142) + _tmp32 * p_camera_source(0, 0);
  const Scalar _tmp160 = _tmp11 * (_tmp101 + _tmp146) + _tmp21 * _tmp9;
  const Scalar _tmp161 =
      _tmp11 * (_tmp104 + _tmp8) + _tmp21 * (_tmp100 + _tmp143 + _tmp19 + _tmp95);
  const Scalar _tmp162 = _tmp159 * _tmp51 + _tmp160 * _tmp56 + _tmp161 * _tmp55;
  const Scalar _tmp163 = _tmp159 * _tmp63 + _tmp160 * _tmp65 + _tmp161 * _tmp62;
  const Scalar _tmp164 = _tmp159 * _tmp29 + _tmp160 * _tmp4 + _tmp161 * _tmp41;
  const Scalar _tmp165 =
      -_tmp109 * _tmp162 + _tmp112 * _tmp163 - _tmp113 * _tmp162 + _tmp115 * _tmp164;
  const Scalar _tmp166 = _tmp117 * _tmp165 + _tmp118 * _tmp165 + _tmp165 * _tmp72;
  const Scalar _tmp167 = _tmp127 * _tmp166 - _tmp128 * _tmp162 + _tmp164 * _tmp75;
  const Scalar _tmp168 = _tmp120 * _tmp166 + _tmp121 * _tmp163 - _tmp123 * _tmp162;
  const Scalar _tmp169 = _tmp125 * _tmp168 + _tmp130 * _tmp167;
  const Scalar _tmp170 = _tmp134 * _tmp169 - _tmp137 * _tmp169 + _tmp167 * _tmp92;
  const Scalar _tmp171 = -_tmp139 * _tmp169 + _tmp140 * _tmp169 + _tmp168 * _tmp92;
  const Scalar _tmp172 = _tmp75 * source_inverse_range;
  const Scalar _tmp173 = _tmp172 * _tmp4;
  const Scalar _tmp174 = _tmp128 * source_inverse_range;
  const Scalar _tmp175 = _tmp174 * _tmp56;
  const Scalar _tmp176 = _tmp113 * source_inverse_range;
  const Scalar _tmp177 = _tmp176 * _tmp56;
  const Scalar _tmp178 = _tmp115 * source_inverse_range;
  const Scalar _tmp179 = _tmp178 * _tmp4;
  const Scalar _tmp180 = _tmp112 * source_inverse_range;
  const Scalar _tmp181 = _tmp180 * _tmp65;
  const Scalar _tmp182 = _tmp109 * source_inverse_range;
  const Scalar _tmp183 = _tmp182 * _tmp56;
  const Scalar _tmp184 = -_tmp177 + _tmp179 + _tmp181 - _tmp183;
  const Scalar _tmp185 = _tmp60 * (_tmp117 * _tmp184 + _tmp118 * _tmp184 + _tmp184 * _tmp72);
  const Scalar _tmp186 = _tmp126 * _tmp185 + _tmp173 - _tmp175;
  const Scalar _tmp187 = _tmp121 * source_inverse_range;
  const Scalar _tmp188 = _tmp187 * _tmp65;
  const Scalar _tmp189 = _tmp123 * source_inverse_range;
  const Scalar _tmp190 = _tmp189 * _tmp56;
  const Scalar _tmp191 = _tmp185 * _tmp77 + _tmp188 - _tmp190;
  const Scalar _tmp192 = _tmp125 * _tmp191 + _tmp130 * _tmp186;
  const Scalar _tmp193 = _tmp134 * _tmp192 - _tmp137 * _tmp192 + _tmp186 * _tmp92;
  const Scalar _tmp194 = -_tmp139 * _tmp192 + _tmp140 * _tmp192 + _tmp191 * _tmp92;
  const Scalar _tmp195 = _tmp180 * _tmp62;
  const Scalar _tmp196 = _tmp176 * _tmp55;
  const Scalar _tmp197 = _tmp182 * _tmp55;
  const Scalar _tmp198 = _tmp178 * _tmp41;
  const Scalar _tmp199 = _tmp195 - _tmp196 - _tmp197 + _tmp198;
  const Scalar _tmp200 = _tmp117 * _tmp199 + _tmp118 * _tmp199 + _tmp199 * _tmp72;
  const Scalar _tmp201 = _tmp172 * _tmp41;
  const Scalar _tmp202 = _tmp174 * _tmp55;
  const Scalar _tmp203 = _tmp127 * _tmp200 + _tmp201 - _tmp202;
  const Scalar _tmp204 = _tmp189 * _tmp55;
  const Scalar _tmp205 = _tmp187 * _tmp62;
  const Scalar _tmp206 = _tmp120 * _tmp200 - _tmp204 + _tmp205;
  const Scalar _tmp207 = _tmp125 * _tmp206 + _tmp130 * _tmp203;
  const Scalar _tmp208 = _tmp134 * _tmp207 - _tmp137 * _tmp207 + _tmp203 * _tmp92;
  const Scalar _tmp209 = -_tmp139 * _tmp207 + _tmp140 * _tmp207 + _tmp206 * _tmp92;
  const Scalar _tmp210 = _tmp174 * _tmp51;
  const Scalar _tmp211 = _tmp178 * _tmp29;
  const Scalar _tmp212 = _tmp176 * _tmp51;
  const Scalar _tmp213 = _tmp180 * _tmp63;
  const Scalar _tmp214 = _tmp182 * _tmp51;
  const Scalar _tmp215 = _tmp211 - _tmp212 + _tmp213 - _tmp214;
  const Scalar _tmp216 = _tmp117 * _tmp215 + _tmp118 * _tmp215 + _tmp215 * _tmp72;
  const Scalar _tmp217 = _tmp172 * _tmp29;
  const Scalar _tmp218 = _tmp127 * _tmp216 - _tmp210 + _tmp217;
  const Scalar _tmp219 = _tmp187 * _tmp63;
  const Scalar _tmp220 = _tmp189 * _tmp51;
  const Scalar _tmp221 = _tmp120 * _tmp216 + _tmp219 - _tmp220;
  const Scalar _tmp222 = _tmp125 * _tmp221 + _tmp130 * _tmp218;
  const Scalar _tmp223 = _tmp134 * _tmp222 - _tmp137 * _tmp222 + _tmp218 * _tmp92;
  const Scalar _tmp224 = -_tmp139 * _tmp222 + _tmp140 * _tmp222 + _tmp221 * _tmp92;
  const Scalar _tmp225 = -_tmp49;
  const Scalar _tmp226 = std::pow(_target_pose[3], Scalar(2));
  const Scalar _tmp227 = _tmp225 + _tmp226;
  const Scalar _tmp228 = -_tmp0;
  const Scalar _tmp229 = _tmp2 + _tmp228;
  const Scalar _tmp230 = _tmp38 * (_tmp227 + _tmp229) + _tmp57;
  const Scalar _tmp231 = -_tmp52;
  const Scalar _tmp232 = -_tmp226;
  const Scalar _tmp233 = _tmp232 + _tmp49;
  const Scalar _tmp234 = -_tmp40;
  const Scalar _tmp235 =
      _tmp23 * (_tmp234 + _tmp39) + _tmp38 * (_tmp231 + _tmp54) + _tmp46 * (_tmp229 + _tmp233);
  const Scalar _tmp236 = -_tmp109 * _tmp235 + _tmp112 * _tmp230 - _tmp113 * _tmp235;
  const Scalar _tmp237 = _tmp117 * _tmp236 + _tmp118 * _tmp236 + _tmp236 * _tmp72;
  const Scalar _tmp238 = _tmp127 * _tmp237 - _tmp128 * _tmp235;
  const Scalar _tmp239 = _tmp120 * _tmp237 + _tmp121 * _tmp230 - _tmp123 * _tmp235;
  const Scalar _tmp240 = _tmp125 * _tmp239 + _tmp130 * _tmp238;
  const Scalar _tmp241 = _tmp134 * _tmp240 - _tmp137 * _tmp240 + _tmp238 * _tmp92;
  const Scalar _tmp242 = -_tmp139 * _tmp240 + _tmp140 * _tmp240 + _tmp239 * _tmp92;
  const Scalar _tmp243 = -_tmp2;
  const Scalar _tmp244 = _tmp23 * (_tmp226 + _tmp228 + _tmp243 + _tmp49) + _tmp47;
  const Scalar _tmp245 = _tmp0 + _tmp243;
  const Scalar _tmp246 = -_tmp25;
  const Scalar _tmp247 =
      _tmp23 * (_tmp246 + _tmp28) + _tmp38 * (_tmp233 + _tmp245) + _tmp46 * (_tmp231 + _tmp53);
  const Scalar _tmp248 = -_tmp109 * _tmp244 - _tmp113 * _tmp244 + _tmp115 * _tmp247;
  const Scalar _tmp249 = _tmp117 * _tmp248 + _tmp118 * _tmp248 + _tmp248 * _tmp72;
  const Scalar _tmp250 = _tmp127 * _tmp249 - _tmp128 * _tmp244 + _tmp247 * _tmp75;
  const Scalar _tmp251 = _tmp120 * _tmp249 - _tmp123 * _tmp244;
  const Scalar _tmp252 = _tmp125 * _tmp251 + _tmp130 * _tmp250;
  const Scalar _tmp253 = _tmp134 * _tmp252 - _tmp137 * _tmp252 + _tmp250 * _tmp92;
  const Scalar _tmp254 = -_tmp139 * _tmp252 + _tmp140 * _tmp252 + _tmp251 * _tmp92;
  const Scalar _tmp255 = _tmp46 * (_tmp227 + _tmp245) + _tmp66;
  const Scalar _tmp256 = _tmp23 * (_tmp0 + _tmp2 + _tmp225 + _tmp232) +
                         _tmp38 * (_tmp246 + _tmp27) + _tmp46 * (_tmp234 + _tmp64);
  const Scalar _tmp257 = _tmp112 * _tmp256 + _tmp115 * _tmp255;
  const Scalar _tmp258 = _tmp117 * _tmp257 + _tmp118 * _tmp257 + _tmp257 * _tmp72;
  const Scalar _tmp259 = _tmp120 * _tmp258 + _tmp121 * _tmp256;
  const Scalar _tmp260 = _tmp127 * _tmp258 + _tmp255 * _tmp75;
  const Scalar _tmp261 = _tmp125 * _tmp259 + _tmp130 * _tmp260;
  const Scalar _tmp262 = _tmp134 * _tmp261 - _tmp137 * _tmp261 + _tmp260 * _tmp92;
  const Scalar _tmp263 = -_tmp139 * _tmp261 + _tmp140 * _tmp261 + _tmp259 * _tmp92;
  const Scalar _tmp264 = _tmp177 - _tmp179 - _tmp181 + _tmp183;
  const Scalar _tmp265 = _tmp117 * _tmp264 + _tmp118 * _tmp264 + _tmp264 * _tmp72;
  const Scalar _tmp266 = _tmp127 * _tmp265 - _tmp173 + _tmp175;
  const Scalar _tmp267 = _tmp120 * _tmp265 - _tmp188 + _tmp190;
  const Scalar _tmp268 = _tmp125 * _tmp267 + _tmp130 * _tmp266;
  const Scalar _tmp269 = _tmp134 * _tmp268 - _tmp137 * _tmp268 + _tmp266 * _tmp92;
  const Scalar _tmp270 = -_tmp139 * _tmp268 + _tmp140 * _tmp268 + _tmp267 * _tmp92;
  const Scalar _tmp271 = -_tmp195 + _tmp196 + _tmp197 - _tmp198;
  const Scalar _tmp272 = _tmp117 * _tmp271 + _tmp118 * _tmp271 + _tmp271 * _tmp72;
  const Scalar _tmp273 = _tmp120 * _tmp272 + _tmp204 - _tmp205;
  const Scalar _tmp274 = _tmp127 * _tmp272 - _tmp201 + _tmp202;
  const Scalar _tmp275 = _tmp125 * _tmp273 + _tmp130 * _tmp274;
  const Scalar _tmp276 = _tmp134 * _tmp275 - _tmp137 * _tmp275 + _tmp274 * _tmp92;
  const Scalar _tmp277 = -_tmp139 * _tmp275 + _tmp140 * _tmp275 + _tmp273 * _tmp92;
  const Scalar _tmp278 = -_tmp211 + _tmp212 - _tmp213 + _tmp214;
  const Scalar _tmp279 = _tmp117 * _tmp278 + _tmp118 * _tmp278 + _tmp278 * _tmp72;
  const Scalar _tmp280 = _tmp127 * _tmp279 + _tmp210 - _tmp217;
  const Scalar _tmp281 = _tmp120 * _tmp279 - _tmp219 + _tmp220;
  const Scalar _tmp282 =
      (Scalar(1) / Scalar(2)) * _tmp125 * _tmp281 + (Scalar(1) / Scalar(2)) * _tmp130 * _tmp280;
  const Scalar _tmp283 = _tmp282 * _tmp76;
  const Scalar _tmp284 = _tmp132 * _tmp283 - _tmp135 * _tmp283 + _tmp280 * _tmp92;
  const Scalar _tmp285 = _tmp282 * _tmp78;
  const Scalar _tmp286 = _tmp132 * _tmp285 - _tmp135 * _tmp285 + _tmp281 * _tmp92;
  const Scalar _tmp287 = _tmp22 * _tmp56 + _tmp37 * _tmp51 + _tmp45 * _tmp55;
  const Scalar _tmp288 = _tmp22 * _tmp4 + _tmp29 * _tmp37 + _tmp41 * _tmp45;
  const Scalar _tmp289 = _tmp22 * _tmp65 + _tmp37 * _tmp63 + _tmp45 * _tmp62;
  const Scalar _tmp290 =
      -_tmp109 * _tmp287 + _tmp112 * _tmp289 - _tmp113 * _tmp287 + _tmp115 * _tmp288;
  const Scalar _tmp291 = _tmp117 * _tmp290 + _tmp118 * _tmp290 + _tmp290 * _tmp72;
  const Scalar _tmp292 = _tmp127 * _tmp291 - _tmp128 * _tmp287 + _tmp288 * _tmp75;
  const Scalar _tmp293 = _tmp120 * _tmp291 + _tmp121 * _tmp289 - _tmp123 * _tmp287;
  const Scalar _tmp294 = _tmp125 * _tmp293 + _tmp130 * _tmp292;
  const Scalar _tmp295 = _tmp134 * _tmp294 - _tmp137 * _tmp294 + _tmp292 * _tmp92;
  const Scalar _tmp296 = -_tmp139 * _tmp294 + _tmp140 * _tmp294 + _tmp293 * _tmp92;

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _res = (*res);

    _res(0, 0) = _tmp93;
    _res(1, 0) = _tmp94;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 2, 13>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp138;
    _jacobian(1, 0) = _tmp141;
    _jacobian(0, 1) = _tmp157;
    _jacobian(1, 1) = _tmp158;
    _jacobian(0, 2) = _tmp170;
    _jacobian(1, 2) = _tmp171;
    _jacobian(0, 3) = _tmp193;
    _jacobian(1, 3) = _tmp194;
    _jacobian(0, 4) = _tmp208;
    _jacobian(1, 4) = _tmp209;
    _jacobian(0, 5) = _tmp223;
    _jacobian(1, 5) = _tmp224;
    _jacobian(0, 6) = _tmp241;
    _jacobian(1, 6) = _tmp242;
    _jacobian(0, 7) = _tmp253;
    _jacobian(1, 7) = _tmp254;
    _jacobian(0, 8) = _tmp262;
    _jacobian(1, 8) = _tmp263;
    _jacobian(0, 9) = _tmp269;
    _jacobian(1, 9) = _tmp270;
    _jacobian(0, 10) = _tmp276;
    _jacobian(1, 10) = _tmp277;
    _jacobian(0, 11) = _tmp284;
    _jacobian(1, 11) = _tmp286;
    _jacobian(0, 12) = _tmp295;
    _jacobian(1, 12) = _tmp296;
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 13, 13>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(_tmp138, Scalar(2)) + std::pow(_tmp141, Scalar(2));
    _hessian(1, 0) = _tmp138 * _tmp157 + _tmp141 * _tmp158;
    _hessian(2, 0) = _tmp138 * _tmp170 + _tmp141 * _tmp171;
    _hessian(3, 0) = _tmp138 * _tmp193 + _tmp141 * _tmp194;
    _hessian(4, 0) = _tmp138 * _tmp208 + _tmp141 * _tmp209;
    _hessian(5, 0) = _tmp138 * _tmp223 + _tmp141 * _tmp224;
    _hessian(6, 0) = _tmp138 * _tmp241 + _tmp141 * _tmp242;
    _hessian(7, 0) = _tmp138 * _tmp253 + _tmp141 * _tmp254;
    _hessian(8, 0) = _tmp138 * _tmp262 + _tmp141 * _tmp263;
    _hessian(9, 0) = _tmp138 * _tmp269 + _tmp141 * _tmp270;
    _hessian(10, 0) = _tmp138 * _tmp276 + _tmp141 * _tmp277;
    _hessian(11, 0) = _tmp138 * _tmp284 + _tmp141 * _tmp286;
    _hessian(12, 0) = _tmp138 * _tmp295 + _tmp141 * _tmp296;
    _hessian(0, 1) = 0;
    _hessian(1, 1) = std::pow(_tmp157, Scalar(2)) + std::pow(_tmp158, Scalar(2));
    _hessian(2, 1) = _tmp157 * _tmp170 + _tmp158 * _tmp171;
    _hessian(3, 1) = _tmp157 * _tmp193 + _tmp158 * _tmp194;
    _hessian(4, 1) = _tmp157 * _tmp208 + _tmp158 * _tmp209;
    _hessian(5, 1) = _tmp157 * _tmp223 + _tmp158 * _tmp224;
    _hessian(6, 1) = _tmp157 * _tmp241 + _tmp158 * _tmp242;
    _hessian(7, 1) = _tmp157 * _tmp253 + _tmp158 * _tmp254;
    _hessian(8, 1) = _tmp157 * _tmp262 + _tmp158 * _tmp263;
    _hessian(9, 1) = _tmp157 * _tmp269 + _tmp158 * _tmp270;
    _hessian(10, 1) = _tmp157 * _tmp276 + _tmp158 * _tmp277;
    _hessian(11, 1) = _tmp157 * _tmp284 + _tmp158 * _tmp286;
    _hessian(12, 1) = _tmp157 * _tmp295 + _tmp158 * _tmp296;
    _hessian(0, 2) = 0;
    _hessian(1, 2) = 0;
    _hessian(2, 2) = std::pow(_tmp170, Scalar(2)) + std::pow(_tmp171, Scalar(2));
    _hessian(3, 2) = _tmp170 * _tmp193 + _tmp171 * _tmp194;
    _hessian(4, 2) = _tmp170 * _tmp208 + _tmp171 * _tmp209;
    _hessian(5, 2) = _tmp170 * _tmp223 + _tmp171 * _tmp224;
    _hessian(6, 2) = _tmp170 * _tmp241 + _tmp171 * _tmp242;
    _hessian(7, 2) = _tmp170 * _tmp253 + _tmp171 * _tmp254;
    _hessian(8, 2) = _tmp170 * _tmp262 + _tmp171 * _tmp263;
    _hessian(9, 2) = _tmp170 * _tmp269 + _tmp171 * _tmp270;
    _hessian(10, 2) = _tmp170 * _tmp276 + _tmp171 * _tmp277;
    _hessian(11, 2) = _tmp170 * _tmp284 + _tmp171 * _tmp286;
    _hessian(12, 2) = _tmp170 * _tmp295 + _tmp171 * _tmp296;
    _hessian(0, 3) = 0;
    _hessian(1, 3) = 0;
    _hessian(2, 3) = 0;
    _hessian(3, 3) = std::pow(_tmp193, Scalar(2)) + std::pow(_tmp194, Scalar(2));
    _hessian(4, 3) = _tmp193 * _tmp208 + _tmp194 * _tmp209;
    _hessian(5, 3) = _tmp193 * _tmp223 + _tmp194 * _tmp224;
    _hessian(6, 3) = _tmp193 * _tmp241 + _tmp194 * _tmp242;
    _hessian(7, 3) = _tmp193 * _tmp253 + _tmp194 * _tmp254;
    _hessian(8, 3) = _tmp193 * _tmp262 + _tmp194 * _tmp263;
    _hessian(9, 3) = _tmp193 * _tmp269 + _tmp194 * _tmp270;
    _hessian(10, 3) = _tmp193 * _tmp276 + _tmp194 * _tmp277;
    _hessian(11, 3) = _tmp193 * _tmp284 + _tmp194 * _tmp286;
    _hessian(12, 3) = _tmp193 * _tmp295 + _tmp194 * _tmp296;
    _hessian(0, 4) = 0;
    _hessian(1, 4) = 0;
    _hessian(2, 4) = 0;
    _hessian(3, 4) = 0;
    _hessian(4, 4) = std::pow(_tmp208, Scalar(2)) + std::pow(_tmp209, Scalar(2));
    _hessian(5, 4) = _tmp208 * _tmp223 + _tmp209 * _tmp224;
    _hessian(6, 4) = _tmp208 * _tmp241 + _tmp209 * _tmp242;
    _hessian(7, 4) = _tmp208 * _tmp253 + _tmp209 * _tmp254;
    _hessian(8, 4) = _tmp208 * _tmp262 + _tmp209 * _tmp263;
    _hessian(9, 4) = _tmp208 * _tmp269 + _tmp209 * _tmp270;
    _hessian(10, 4) = _tmp208 * _tmp276 + _tmp209 * _tmp277;
    _hessian(11, 4) = _tmp208 * _tmp284 + _tmp209 * _tmp286;
    _hessian(12, 4) = _tmp208 * _tmp295 + _tmp209 * _tmp296;
    _hessian(0, 5) = 0;
    _hessian(1, 5) = 0;
    _hessian(2, 5) = 0;
    _hessian(3, 5) = 0;
    _hessian(4, 5) = 0;
    _hessian(5, 5) = std::pow(_tmp223, Scalar(2)) + std::pow(_tmp224, Scalar(2));
    _hessian(6, 5) = _tmp223 * _tmp241 + _tmp224 * _tmp242;
    _hessian(7, 5) = _tmp223 * _tmp253 + _tmp224 * _tmp254;
    _hessian(8, 5) = _tmp223 * _tmp262 + _tmp224 * _tmp263;
    _hessian(9, 5) = _tmp223 * _tmp269 + _tmp224 * _tmp270;
    _hessian(10, 5) = _tmp223 * _tmp276 + _tmp224 * _tmp277;
    _hessian(11, 5) = _tmp223 * _tmp284 + _tmp224 * _tmp286;
    _hessian(12, 5) = _tmp223 * _tmp295 + _tmp224 * _tmp296;
    _hessian(0, 6) = 0;
    _hessian(1, 6) = 0;
    _hessian(2, 6) = 0;
    _hessian(3, 6) = 0;
    _hessian(4, 6) = 0;
    _hessian(5, 6) = 0;
    _hessian(6, 6) = std::pow(_tmp241, Scalar(2)) + std::pow(_tmp242, Scalar(2));
    _hessian(7, 6) = _tmp241 * _tmp253 + _tmp242 * _tmp254;
    _hessian(8, 6) = _tmp241 * _tmp262 + _tmp242 * _tmp263;
    _hessian(9, 6) = _tmp241 * _tmp269 + _tmp242 * _tmp270;
    _hessian(10, 6) = _tmp241 * _tmp276 + _tmp242 * _tmp277;
    _hessian(11, 6) = _tmp241 * _tmp284 + _tmp242 * _tmp286;
    _hessian(12, 6) = _tmp241 * _tmp295 + _tmp242 * _tmp296;
    _hessian(0, 7) = 0;
    _hessian(1, 7) = 0;
    _hessian(2, 7) = 0;
    _hessian(3, 7) = 0;
    _hessian(4, 7) = 0;
    _hessian(5, 7) = 0;
    _hessian(6, 7) = 0;
    _hessian(7, 7) = std::pow(_tmp253, Scalar(2)) + std::pow(_tmp254, Scalar(2));
    _hessian(8, 7) = _tmp253 * _tmp262 + _tmp254 * _tmp263;
    _hessian(9, 7) = _tmp253 * _tmp269 + _tmp254 * _tmp270;
    _hessian(10, 7) = _tmp253 * _tmp276 + _tmp254 * _tmp277;
    _hessian(11, 7) = _tmp253 * _tmp284 + _tmp254 * _tmp286;
    _hessian(12, 7) = _tmp253 * _tmp295 + _tmp254 * _tmp296;
    _hessian(0, 8) = 0;
    _hessian(1, 8) = 0;
    _hessian(2, 8) = 0;
    _hessian(3, 8) = 0;
    _hessian(4, 8) = 0;
    _hessian(5, 8) = 0;
    _hessian(6, 8) = 0;
    _hessian(7, 8) = 0;
    _hessian(8, 8) = std::pow(_tmp262, Scalar(2)) + std::pow(_tmp263, Scalar(2));
    _hessian(9, 8) = _tmp262 * _tmp269 + _tmp263 * _tmp270;
    _hessian(10, 8) = _tmp262 * _tmp276 + _tmp263 * _tmp277;
    _hessian(11, 8) = _tmp262 * _tmp284 + _tmp263 * _tmp286;
    _hessian(12, 8) = _tmp262 * _tmp295 + _tmp263 * _tmp296;
    _hessian(0, 9) = 0;
    _hessian(1, 9) = 0;
    _hessian(2, 9) = 0;
    _hessian(3, 9) = 0;
    _hessian(4, 9) = 0;
    _hessian(5, 9) = 0;
    _hessian(6, 9) = 0;
    _hessian(7, 9) = 0;
    _hessian(8, 9) = 0;
    _hessian(9, 9) = std::pow(_tmp269, Scalar(2)) + std::pow(_tmp270, Scalar(2));
    _hessian(10, 9) = _tmp269 * _tmp276 + _tmp270 * _tmp277;
    _hessian(11, 9) = _tmp269 * _tmp284 + _tmp270 * _tmp286;
    _hessian(12, 9) = _tmp269 * _tmp295 + _tmp270 * _tmp296;
    _hessian(0, 10) = 0;
    _hessian(1, 10) = 0;
    _hessian(2, 10) = 0;
    _hessian(3, 10) = 0;
    _hessian(4, 10) = 0;
    _hessian(5, 10) = 0;
    _hessian(6, 10) = 0;
    _hessian(7, 10) = 0;
    _hessian(8, 10) = 0;
    _hessian(9, 10) = 0;
    _hessian(10, 10) = std::pow(_tmp276, Scalar(2)) + std::pow(_tmp277, Scalar(2));
    _hessian(11, 10) = _tmp276 * _tmp284 + _tmp277 * _tmp286;
    _hessian(12, 10) = _tmp276 * _tmp295 + _tmp277 * _tmp296;
    _hessian(0, 11) = 0;
    _hessian(1, 11) = 0;
    _hessian(2, 11) = 0;
    _hessian(3, 11) = 0;
    _hessian(4, 11) = 0;
    _hessian(5, 11) = 0;
    _hessian(6, 11) = 0;
    _hessian(7, 11) = 0;
    _hessian(8, 11) = 0;
    _hessian(9, 11) = 0;
    _hessian(10, 11) = 0;
    _hessian(11, 11) = std::pow(_tmp284, Scalar(2)) + std::pow(_tmp286, Scalar(2));
    _hessian(12, 11) = _tmp284 * _tmp295 + _tmp286 * _tmp296;
    _hessian(0, 12) = 0;
    _hessian(1, 12) = 0;
    _hessian(2, 12) = 0;
    _hessian(3, 12) = 0;
    _hessian(4, 12) = 0;
    _hessian(5, 12) = 0;
    _hessian(6, 12) = 0;
    _hessian(7, 12) = 0;
    _hessian(8, 12) = 0;
    _hessian(9, 12) = 0;
    _hessian(10, 12) = 0;
    _hessian(11, 12) = 0;
    _hessian(12, 12) = std::pow(_tmp295, Scalar(2)) + std::pow(_tmp296, Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 13, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp138 * _tmp93 + _tmp141 * _tmp94;
    _rhs(1, 0) = _tmp157 * _tmp93 + _tmp158 * _tmp94;
    _rhs(2, 0) = _tmp170 * _tmp93 + _tmp171 * _tmp94;
    _rhs(3, 0) = _tmp193 * _tmp93 + _tmp194 * _tmp94;
    _rhs(4, 0) = _tmp208 * _tmp93 + _tmp209 * _tmp94;
    _rhs(5, 0) = _tmp223 * _tmp93 + _tmp224 * _tmp94;
    _rhs(6, 0) = _tmp241 * _tmp93 + _tmp242 * _tmp94;
    _rhs(7, 0) = _tmp253 * _tmp93 + _tmp254 * _tmp94;
    _rhs(8, 0) = _tmp262 * _tmp93 + _tmp263 * _tmp94;
    _rhs(9, 0) = _tmp269 * _tmp93 + _tmp270 * _tmp94;
    _rhs(10, 0) = _tmp276 * _tmp93 + _tmp277 * _tmp94;
    _rhs(11, 0) = _tmp284 * _tmp93 + _tmp286 * _tmp94;
    _rhs(12, 0) = _tmp295 * _tmp93 + _tmp296 * _tmp94;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
