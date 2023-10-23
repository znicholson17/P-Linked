import os

def set_up_esp32_cmake_project(project_name, target_chip="esp32", template_dir=None):
  """Sets up an ESP32 CMake project.

  Args:
    project_name: The name of the project.
    target_chip: The target chip to build for.
    template_dir: The path to the template directory.
  """

  # Create the project directory.
  project_dir = os.path.join(os.getcwd(), project_name)
  os.makedirs(project_dir, exist_ok=True)

  # Copy the template directory into the new project directory.
  if template_dir is not None:
    copy_template(template_dir, project_dir)

  # Create the CMakeLists.txt file.
  with open(os.path.join(project_dir, "CMakeLists.txt"), "w") as f:
    f.write("""
cmake_minimum_required(VERSION 3.16)

project(${PROJECT_NAME})

set(IDF_TARGET ${IDF_TARGET})

include($ENV{IDF_PATH}/tools/idf.cmake)
""")

  # Set the target chip.
  os.system(f"idf.py set-target {target_chip}")

  # Print a message to the user.
  print("ESP32 CMake project set up successfully!")


def copy_template(template_dir, project_dir):
  """Copies the contents of a template directory into a new project directory.

  Args:
    template_dir: The path to the template directory.
    project_dir: The path to the new project directory.
  """

  for root, dirs, files in os.walk(template_dir):
    for file in files:
      src_path = os.path.join(root, file)
      dst_path = os.path.join(project_dir, root.replace(template_dir, ""), file)
      os.makedirs(os.path.dirname(dst_path), exist_ok=True)
      os.copyfile(src_path, dst_path)


if __name__ == "__main__":
  project_name = input("Enter the name of the project: ")
  target_chip = input("Enter the target chip (esp32 or esp32s3): ") or "esp32s3"
  template_dir = input("Enter the path to the template directory (optional): ") or None

  set_up_esp32_cmake_project(project_name, target_chip, template_dir)



