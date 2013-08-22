#include <string>
#include <fstream>
#include <vector>
#include <iostream>

template <typename dataType>
void appendData(std::vector<unsigned char> *vector, dataType data) {
  vector->insert(vector->end(), reinterpret_cast<unsigned char *>(&data),
      reinterpret_cast<unsigned char *>((&data)+ 1));
}

int main() {
  std::vector<unsigned char> output;
  int length = 3;
  appendData<int>(&output, length);

  appendData<int>(&output, 0);
  appendData<int>(&output, 1);
  appendData<int>(&output, 2);

  int numVerts = 3;
  appendData<int>(&output, numVerts);

  //Write positions
  appendData<float>(&output, 0.0f);
  appendData<float>(&output, 1.0f);
  appendData<float>(&output, 0.0f);

  appendData<float>(&output, 1.0f);
  appendData<float>(&output, 0.0f);
  appendData<float>(&output, 0.0f);

  appendData<float>(&output, 0.5f);
  appendData<float>(&output, 0.5f);
  appendData<float>(&output, 0.0f);

  //Write normals
  appendData<float>(&output, 1.0f);
  appendData<float>(&output, 0.0f);
  appendData<float>(&output, 0.0f);

  appendData<float>(&output, 1.0f);
  appendData<float>(&output, 0.0f);
  appendData<float>(&output, 0.0f);

  appendData<float>(&output, 0.0f);
  appendData<float>(&output, 1.0f);
  appendData<float>(&output, 0.0f);

  std::ofstream file;
  file.open("triangle.geo", std::ios::out | std::ios::binary | std::ios::trunc);
  file.write(reinterpret_cast<char *>(output.data()), output.size());
  std::cout << output.size() << std::endl;
  for (int i=0; i < output.size()/4; ++i) {
    std::cout << (int) output[i*4] << " " << (int) output[i*4+1] << " "<< (int) output[i*4+2] << " " << (int) output[i*4+3] << std::endl;
  }
  return 0;
}
