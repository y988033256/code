<!doctype html>
<html lang="en">
<head>
    <link  rel="stylesheet" type="text/css" href="index.css"/>
    <meta charset="UTF-8" />
    <title>Admin </title>
</head>
<body>
<div class="header">
    <p>Update success</p>
</div>
<div class="form">
<?php
include 'database_conn.php';      // make db connection
$eventID = isset($_REQUEST['eventID'])?$_REQUEST['eventID']:null;
$eventTitle = isset($_REQUEST['eventTitle'])?$_REQUEST['eventTitle']:null;    // Prevent undefined index error notice messages following submission of the form
$eventDescription= isset($_REQUEST['eventDescription'])?$_REQUEST['eventDescription']:null;
$venueName = isset($_REQUEST['Venuename'])?$_REQUEST['Venuename']:null;      //Prompt the user to enter data / make a choice if they do not do so for a required field
$catDesc = isset($_REQUEST['catDesc'])?$_REQUEST['catDesc']:null;
$eventStartDate = isset($_REQUEST['eventStartDate'])?$_REQUEST['eventStartDate']:null;
$eventEndDate = isset($_REQUEST['eventEndDate'])?$_REQUEST['eventEndDate']:null;
$eventPrice = isset($_REQUEST['eventPrice'])?$_REQUEST['eventPrice']:null;

$eventID = $dbConn->real_escape_string($eventID);
$eventTitle = $dbConn->real_escape_string($eventTitle);
$venueName = $dbConn->real_escape_string($venueName);
$catDesc = $dbConn->real_escape_string($catDesc);               //Escape any special characters that may have been entered by the users
$eventDescription = $dbConn->real_escape_string($eventDescription);
$eventStartDate = $dbConn->real_escape_string($eventStartDate);
$eventEndDate = $dbConn->real_escape_string($eventEndDate);
$eventPrice = $dbConn->real_escape_string($eventPrice);

if (empty($eventID)){
    echo "<p>Sorry enter the Event ID please</p>\n";       // if dont have date i will tell user to re enter data
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if (empty($eventTitle)){
    echo "<p>Sorry enter the Title please</p>\n";           // if dont have date i will tell user to re enter data
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if  (empty($eventDescription)){               // if dont have date i will tell user to re enter data
    echo "<p>Sorry enter the Description please</p>\n";
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if (empty($venueName)){
    echo "<p>Sorry enter the venue please</p>\n";            // if dont have date i will tell user to re enter data
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if (empty($catDesc)){
    echo "<p>Sorry enter the category please</p>\n";            // if dont have date i will tell user to re enter data
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if  (empty($eventStartDate)){                                   // if dont have date i will tell user to re enter data
    echo "<p>Sorry enter the event start date please</p>\n";
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if  (empty($eventEndDate)){                                      // if dont have date i will tell user to re enter data
    echo "<p>Sorry enter the event end date please</p>\n";
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if  (empty($eventPrice)){
    echo "<p>Sorry enter the price please</p>\n";                        // if dont have date i will tell user to re enter data
    echo '<a href="admin.php"><button>Go Back</button>';
}
else{
    $updateSQL = "UPDATE unn_w15020771.AE_events 
                  INNER JOIN AE_category ON AE_category.catID = AE_events.catID 
                  INNER JOIN AE_venue ON AE_venue.venueID = AE_events. venueID
                  SET AE_venue.venueName = '$venueName',
                      AE_category.catDesc = '$catDesc',
                      AE_events.eventTitle = '$eventTitle',
                      AE_events.eventDescription = '$eventDescription',                
                      AE_events.eventStartDate = '$eventStartDate',
                      AE_events.eventEndDate = '$eventEndDate', 
                      AE_events.eventPrice = '$eventPrice'
                  WHERE AE_events.eventID = $eventID";                                    //Construct an SQL query
    $success = $dbConn->query($updateSQL);
                                                                 // the table to display the detail that have been updated
    echo "<form method='post' action='admin.php'>
             <fieldset>
                 <legend><h2>Event ID:$eventID have been updated<input type='hidden' name='eventID' value= '$eventID'></h2></legend>                 
                     <table class='updateDetail'>
                         <tr>
                           <td>Title:</td>                               
                           <td>$eventTitle</td>
                         </tr>
                         <tr>
                           <td>Venue:</td>
                           <td>$venueName</td>
                         </tr>
                         <tr>
                           <td>Category:</td>
                           <td>$catDesc</td>
                         </tr>          
                         <tr>
                           <td>Start Date:</td>
                           <td>$eventStartDate</td>
                         </tr>
                         <tr>
                           <td>End Date:</td>
                           <td>$eventEndDate</td>
                         </tr>
                         <tr>
                           <td>Price(£):</td>
                           <td>$eventPrice</td>
                         </tr>
                     </table>
                     <p>Description</p>
                     <p><textarea name='eventDescription'style='width:50%; height:120px; font-family: Calibri; font-size:15px;'>$eventDescription</textarea></p>          
                     <p><input type='submit' value='Back' /><p>
             </fieldset>
        </form>";
}
$dbConn->close();
?>
</div>
</body>
</html>
</html>