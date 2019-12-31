#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor():coreId(-1){};
  Processor(int coreId):coreId(coreId){};

  // TODO: Declare any necessary private members
 private:
    float cpuUsage;
    int coreId;
};

#endif