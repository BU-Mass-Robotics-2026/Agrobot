from setuptools import find_packages, setup

package_name = "agrobot_supervisor"

setup(
    name=package_name,
    version="0.1.0",
    packages=find_packages(exclude=["test"]),
    data_files=[
        ("share/ament_index/resource_index/packages",
            ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        ("share/" + package_name + "/launch", ["launch/supervisor.launch.py"]),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="Agrobot Team",
    maintainer_email="robotics-club@example.com",
    description="Discrete step-and-shoot picking supervisor for Agrobot TOM v2.",
    license="MIT",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "supervisor = agrobot_supervisor.supervisor_node:main",
        ],
    },
)
