<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

include_once 'config.php';
if(isset($_POST['buttonclick']))
{    
     
 $file = rand(1000,100000)."-".$_FILES['file']['name'];
    $file_loc = $_FILES['file']['tmp_name'];
 $file_size = $_FILES['file']['size'];
 $file_type = $_FILES['file']['type'];
 $folder="/tmp/";
 
 // new file size in KB
 $new_size = $file_size/1024;  
 // new file size in KB
 
 // make file name in lower case
 $new_file_name = strtolower($file);
 // make file name in lower case
 
 $final_file=str_replace(' ','-',$new_file_name);
 echo $file_loc;
 echo $folder.$final_file;
 echo $_FILES['file']['error'];
 echo UPLOAD_ERR_OK;
 if(move_uploaded_file($file_loc,$folder.$final_file))
 {
  echo "This is done"
  // $sql="INSERT INTO displaydata(location,size,type) VALUES('$final_file','$new_size','$file_type')";
  // mysql_query($sql);
  ?>
  <script>
  alert('successfully uploaded');
        // window.location.href='index.php?success';
        </script>
  <?php
 }
 else
 {
  ?>
  <script>
  alert('error while uploading file');
        // window.location.href='index.php?fail';
        </script>
  <?php
 }
}
?>