Facial recognition

Step 1: Access to webcam
step 2: Face identification.
step 3: Data collection
Step 4: Training
step 5: Face recognition
step 6: Programming Arduino

Step 1: Access to Webcam
The 1st step for facial recognition was to have access to a camera or a computer vision. Since India is under lockdown the cheapest solution which I found was to use my computers webcam to which I had access with a python program using openCV module.
You might be thinking what is OpenCV, isn't it?
OpenCV (Open Source Computer Vision Library) is an open-source computer vision and machine learning software library. OpenCV was built to provide a common infrastructure for computer vision applications and to accelerate the use of machine perception in commercial products.
If Opencv is installed on your computer then you are good to go. If not then follow this step.
open command prompt and type "pip install opencv".
Warning: You may get an error as "'pip' is not recognized as an internal or external command". for which You need to add the path of your pip installation to your PATH system variable. Go through this post it may help you.
https://stackoverflow.com/questions/23708898/pip-i...
Once OpenCV is installed we are good to go... To check if its properly installed open your Python interpreter and import the library. See the image above that should be your output.
Download the python file "AccessTo_webcam.py" and run it. I have provided all the necessary comments there.
There you go, Now you have access to the webcam. Well done. 

Step 2: Face Identification.
Face Identification.
with the help of the same OpenCV module, we have to identify whether there is a face on the video stream or not.
OpenCV provides a training method or pre-trained models called as Cascade Classifier. The pre-trained models are located in the data folder in the OpenCV installation. I'm providing that file just download it and place it in your project folder. The folder where the "AccessTo_webcam.py" file is stored. If you have not created one then do it.
Download "haarcascade_frontalface_default" and place it in the main project folder.
Download "Face_identification.py" and place it in the main project folder. All the explanation is provided in it.
Now you can identify the faces in a video stream. 

Step 3: Data Collection
Data Collection
To recognize the faces we need to train our python program. For which we need some data.
Data collection is rather the easiest step in this project. create a folder named "image_data" in your main project folder. Inside the "image_data" folder create some additional folders with the person's name, where we will store the data. for example:
In the "image_data" folder I have created two more folders named "HRK" and "Yahiya". as shown in the above image.
Now go ahead create your own folders and name them.
Once the folders are created then start collecting images of that specific person. I recommend collecting nearly about 20 images per person. You can also add more images but see to it that data collected for all the persons contains the same number of images. It helps to provide accuracy.

Step 4: Training
In brief, we will go through all the folders and images which are present in the "image_data" folder and create a dictionary that will contain the label ID and the corresponding name. Simultaneously we will load the image to detect the face in each and every image which we call it "Region of Interest" and create a ".yml" file which contains that information.
Assuming that you have data collected for person X and Y.
we will label person X as 1 which will be his label ID and name will be X itself. We load the image to find his face i.e Region of interest and append the data to a list.
similar steps will be followed for person Y. And finally, we will create a ".yml" file.
Download the "face_trainer.py" file and place it in the main project folder. All the necessary explanation is provided in that file itself.
When you run this program it will go through all the images and create two files named "labels.pickle" and "trainner.yml". Now you have trained your own model. 

Step 5: Face Recognition
Face Recognition
If you have gone through all the steps properly then you may have created your own trained data. Now we will use that data for face recognition.
Basically we will load our trained models into the python file, Access our webcam, and identify Faces in the video stream and do a comparison or prediction between the current face which is identified in the video stream, and the model which was trained. if the data is matched then we say that the person is recognized it is just that simple...
Download "face_recognise.py" and run it. All the necessary information is provided in it. Now your face may have been recognized. if the accuracy is not good then try updating the data. if you are all good to go then lets proceed to step 6/

Step 6: Programming Arduino
The last and the final step is programming Arduino, And to provide a mode of communication between python and Arduino. For communication, I used "Serial Communication". Go through the video which I have linked above to find how Serial Communication works and to establish one.You will find all the required files in the video description.
If you have gone through the video then let me explain to you what I did. When my face is recognized then the label ID provided is 2. Once label ID is 2 I will send '1' as the serial data to my Arduino. Which will turn on my LED chaser circuit. If label ID is other than 2 then i will send '0' as the serial data, which will turn off my LED chaser Circuit.
Download the "ard_chaser.ino" file. It is a simple LED chaser program that uses serial communication.
Simillerly download "face_recogniser1.py" that will establish the serial communication between Arduino and the python program.

It's done............
