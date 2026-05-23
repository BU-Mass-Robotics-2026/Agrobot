import os
from glob import glob
from setuptools import find_packages, setup

package_name = 'copley_bridge'

setup(
    name=package_name,
    version='0.0.1',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
        (os.path.join('share', package_name, 'scripts'), glob('scripts/*.sh')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robotics-club',
    maintainer_email='bostonuniversityrobotics@gmail.com',
    description='ROS 2 bridge for Copley Controls APZ-090-50 (CANopen) drives.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'copley_joint_bridge = copley_bridge.copley_joint_bridge:main',
        ],
    },
)
