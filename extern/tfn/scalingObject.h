#ifndef SCALINGOBJECT_H
#define SCALINGOBJECT_H 

#include <vector>
#include "math_def.h"

typedef ovr::math::vec2f vec2f;

struct ScalingObject {
  private:
    float* slopes = new float[3];
    float* intercepts = new float[2];
    bool scalingActive = false;

    static ScalingObject* instance;

    ScalingObject() {
      UpdateValues();
    }

    void UpdateValues() {
      slopes[0] = (scalingPoints[1].y - scalingPoints[0].y) / (scalingPoints[1].x - scalingPoints[0].x);
      slopes[1] = (scalingPoints[2].y - scalingPoints[1].y) / (scalingPoints[2].x - scalingPoints[1].x);
      intercepts[0] = scalingPoints[1].y - (slopes[1] * scalingPoints[1].x);
      slopes[2] = (scalingPoints[3].y - scalingPoints[2].y) / (scalingPoints[3].x - scalingPoints[2].x);
      intercepts[1] = scalingPoints[2].y - (slopes[2] * scalingPoints[2].x);
    }
  
  public:
    std::vector<vec2f> scalingPoints = {{0, 0}, {0.3, 0.1}, {0.7, 0.9}, {1, 1}};
    ScalingObject(const ScalingObject& obj) = delete;

    static ScalingObject* GetScalingObject() {
      if (instance == nullptr) {
        instance = new ScalingObject();
      }
      return instance;
    }

    bool* ScalingStatus() {
      return &scalingActive;
    }

    float GetScaledOutput(float x_pos) {
      UpdateValues();

      if (x_pos < scalingPoints[1].x) {
        return slopes[0] * x_pos;
      }
      else if (x_pos > scalingPoints[2].x) {
        return (slopes[2] * x_pos) + intercepts[1];
      }
      else {
        return (slopes[1] * x_pos) + intercepts[0];
      }
    }
};

#endif