function varargout = app(varargin)

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @app_OpeningFcn, ...
                   'gui_OutputFcn',  @app_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

% --- Executes just before app is made visible.
function app_OpeningFcn(hObject, eventdata, handles, varargin)

% Choose default command line output for app
handles.output = hObject;
handles.imageUploaded = false;
handles.imageProcessed = false;

% Update handles structure
guidata(hObject, handles);

axes(handles.uploadimage);
axis off;


% --- Outputs from this function are returned to the command line.
function varargout = app_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in btnOtsu.
function btnOtsu_Callback(hObject, eventdata, handles)
if(~handles.imageUploaded)
    errordlg('Image to process is not uploaded.','Failed');
   return; 
end
if(handles.grayScaled)
    imageObj = handles.image;
    imageProcessed = imbinarize(imageObj, 'global');
    handles.imageProcessed = true;
    axes(handles.uploadimage);
    imshowpair(imageObj,imageProcessed,'montage');
    title(get(hObject, 'string'));
    guidata(hObject, handles);
else
    errordlg('Image is not gray scaled to perform thresholding','Failed');
end


% --- Executes on button press in btnLocalNiblack.
function btnLocalNiblack_Callback(hObject, eventdata, handles)
if(~handles.imageUploaded)
    errordlg('Image to process is not uploaded.','Failed');
   return; 
end
if(handles.grayScaled)
    imageObj = handles.image;
    imageProcessed = niblack(imageObj);
    handles.imageProcessed = true;
    axes(handles.uploadimage);
    imshowpair(imageObj,imageProcessed,'montage');
    title(get(hObject, 'string'));
    guidata(hObject, handles);
else
    errordlg('Image is not gray scaled to perform thresholding','Failed');
end


% --- Executes on button press in btnLocalBernsen.
function btnLocalBernsen_Callback(hObject, eventdata, handles)
if(~handles.imageUploaded)
    errordlg('Image to process is not uploaded.','Failed');
   return; 
end
if(handles.grayScaled)
    imageObj = handles.image;
    imageProcessed = bernsen(imageObj);
    handles.imageProcessed = true;
    axes(handles.uploadimage);
    imshowpair(imageObj,imageProcessed,'montage');
    title(get(hObject, 'string'));
    guidata(hObject, handles);
else
    errordlg('Image is not gray scaled to perform thresholding','Failed');
end


% --- Executes on button press in btnAdaptive.
function btnAdaptive_Callback(hObject, eventdata, handles)
if(~handles.imageUploaded)
    errordlg('Image to process is not uploaded.','Failed');
   return; 
end
if(handles.grayScaled)
    imageObj = handles.image;
    imageProcessed = imbinarize(imageObj, 'adaptive');
    handles.imageProcessed = true;
    axes(handles.uploadimage);
    imshowpair(imageObj,imageProcessed,'montage');
    title(get(hObject, 'string'));
    guidata(hObject, handles);
else
    errordlg('Image is not gray scaled to perform thresholding','Failed');
end

% --- Executes on button press in btnLaplassian.
function btnLaplassian_Callback(hObject, eventdata, handles)
if(~handles.imageUploaded)
    errordlg('Image to process is not uploaded.','Failed');
   return; 
end
if(handles.grayScaled)
    imageObj = handles.image;
    filter = fspecial('laplacian', 0);
    imageProcessed = imfilter(imageObj, filter);
    handles.imageProcessed = true;
    axes(handles.uploadimage);
    imshowpair(imageObj,imageProcessed,'montage');
    title(get(hObject, 'string'));
    guidata(hObject, handles);
else
    errordlg('Image is not gray scaled to perform thresholding','Failed');
end


% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to uploadpicture (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname] = uigetfile('*.*', 'Choose an Image to process');
if isequal(filename,0) || isequal(pathname,0)
       disp('User pressed cancel')
else
% this command will be used to concate both the file name and path name.
filename=strcat(pathname,filename);
% now to read the image we will use the command imread and save it in the variable “a”.
image=imread(filename);
%Now in order to show it in the first axes we will write the command:
      axes(handles.uploadimage);
      imshow(image);
%Now in order to use this image in other function also we will write the command:
      handles.image = image;
      handles.imageUploaded = true;
      handles.imageProcessed = false;
%Now we determine if the image is gray scale
      handles.grayScaled = ~(size(image,3)==3);

% Update handles structure
      guidata(hObject, handles);
end


% --- Executes on button press in btnConvert.
function btnConvert_Callback(hObject, eventdata, handles)
if(~handles.imageUploaded)
    errordlg('Image to process is not uploaded.','Failed');
   return; 
end
if(handles.grayScaled)
    errordlg('Image is already gray scaled','Failed');
else
    image = rgb2gray(handles.image);
    axes(handles.uploadimage);
    imshow(image);
    handles.image = image;
    handles.grayScaled = true;
    guidata(hObject, handles);
end


% --- Executes on button press in btnSave.
function btnSave_Callback(hObject, eventdata, handles)
if(~handles.imageUploaded || ~handles.imageProcessed)
    errordlg('Image to save is not processed.','Failed');
    return;
end
axes(handles.uploadimage);
saveas(gcf, 'Result Image.png');



% --- Executes on button press in btnLOG.
function btnLOG_Callback(hObject, eventdata, handles)
if(~handles.imageUploaded)
    errordlg('Image to process is not uploaded.','Failed');
   return; 
end
if(handles.grayScaled)
    imageObj = handles.image;
    filter = fspecial('log', 5, 0.5);
    imageProcessed = imfilter(imageObj, filter);
    handles.imageProcessed = true;
    axes(handles.uploadimage);
    imshowpair(imageObj,imageProcessed,'montage');
    title(get(hObject, 'string'));
    guidata(hObject, handles);
else
    errordlg('Image is not gray scaled to perform thresholding','Failed');
end
