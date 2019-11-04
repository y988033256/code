<!doctype html>
<html lang="en">
<head>
    <link  rel="stylesheet" type="text/css" href="index.css"/>
    <meta charset="UTF-8" />
    <title>Admin </title>
</head>
<body>
<div class="header">
    <p>Add event success</p>
</div>
<div class="form">
<?php
include 'database_conn.php';      // make db connection
$eventID = isset($_REQUEST['eventID'])?$_REQUEST['eventID']:null;
$eventTitle = isset($_REQUEST['eventTitle'])?$_REQUEST['eventTitle']:null;
$eventDescription= isset($_REQUEST['eventDescription'])?$_REQUEST['eventDescription']:null;    // Prevent undefined index error notice messages following submission of the form
$VenueID = isset($_REQUEST['VenueID'])?$_REQUEST['VenueID']:null;               //Prompt the user to enter data / make a choice if they do not do so for a required field
$catID = isset($_REQUEST['catID'])?$_REQUEST['catID']:null;
$eventStartDate = isset($_REQUEST['eventStartDate'])?$_REQUEST['eventStartDate']:null;
$eventEndDate = isset($_REQUEST['eventEndDate'])?$_REQUEST['eventEndDate']:null;
$eventPrice = isset($_REQUEST['eventPrice'])?$_REQUEST['eventPrice']:null;

$eventID = $dbConn->real_escape_string($eventID);
$eventTitle = $dbConn->real_escape_string($eventTitle);           //Escape any special characters that may have been entered by the users
$VenueID = $dbConn->real_escape_string($VenueID);
$catID = $dbConn->real_escape_string($catID);
$eventDescription = $dbConn->real_escape_string($eventDescription);
$eventStartDate = $dbConn->real_escape_string($eventStartDate);
$eventEndDate = $dbConn->real_escape_string($eventEndDate);
$eventPrice = $dbConn->real_escape_string($eventPrice);

if (empty($eventTitle)){
    echo "<p>Sorry enter the Title please</p>\n";               // if dont have date i will tell user to re enter data
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if (empty($VenueID)){
    echo "<p>Sorry enter the venue please</p>\n";
    echo '<a href="admin.php"><button>Go Back</button>';            // if dont have date i will tell user to re enter data
}
else if (empty($catID)){
    echo "<p>Sorry enter the category please</p>\n";
    echo '<a href="admin.php"><button>Go Back</button>';          // if dont have date i will tell user to re enter data
}
else if  (empty($eventStartDate)){
    echo "<p>Sorry enter the event start date please</p>\n";      // if dont have date i will tell user to re enter data
    echo '<a href="admin.php"><button>Go Back</button>';
}
else if  (empty($eventEndDate)){
    echo "<p>Sorry enter the event end date please</p>\n";      // if dont have date i will tell user to re enter data
    echo '<a href="admin.php"><button>Go Back</button>';
}
else{
    $addSQL = "INSERT INTO unn_w15020771.AE_events (eventID, eventTitle, eventDescription, venueID, catID, eventStartDate, eventEndDate, eventPrice)
    VALUES (NULL,'$eventTitle', '$eventDescription', '$VenueID', '$catID', '$eventStartDate', '$eventEndDate', '$eventPrice')";      // sql to insert data
    $success = $dbConn->query($addSQL);                // Display the event title, description, start date, end date, price, category and venue for new add event
    echo "<form method='post' action='admin.php'>          
             <fieldset>                                                     
                 <legend><h2>Event have been added</h2></legend>                 
                     <table class='updateDetail'>
                         <tr>
                           <td>Title:</td>
                           <td>$eventTitle</td>
                         </tr>
                         <tr>
                           <td>Venue:</td>";
    $VenuenameSQL = "SELECT venueID,venueName FROM AE_venue Where venueID ='$VenueID'";   // this sql + php code is for  the addevent page
    $VenuenamequeryResult = $dbConn->query($VenuenameSQL);                                // display venuename and category name instand of IDs
    if($VenuenamequeryResult === false){
        echo "<p>Query failed: ".$dbConn->error."</p>\n";
        exit;
    }
    $Venuenamerow = $VenuenamequeryResult->fetch_assoc();
                         echo"<td>$Venuenamerow[venueName]</td>
                         </tr>
                         <tr>
                           <td>Category:</td>";
    $catsql = "SELECT catID,catDesc FROM AE_category WHERE catID='$catID'";             // this sql + php code is for  the addevent page
    $catqueryResult = $dbConn->query($catsql);                                          // display venuename and category name instand of IDs
    if($catqueryResult === false){
        echo "<p>Query failed: ".$dbConn->error."</p>\n";
        exit;
    }
    $catDescrow = $catqueryResult->fetch_assoc();
                           echo"<td>$catDescrow[catDesc]</td>
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
                     <p><textarea name='eventDescription'style='width:55%; height:120px; font-family: Calibri; font-size:15px;'>$eventDescription</textarea></p>          
                     <p><input type='submit' value='Back' /><p>";

                           if ($catID == 'c1' ){                      // image that is relevant to the choice of category
                               echo"<p><img src='Carnival.png' ></p>";
                           }
                           if ($catID == 'c2' ){               // image that is relevant to the choice of category
                               echo"<p><img src='Theatre.png' ></p>";
                           }
                           if ($catID == 'c3' ){                // image that is relevant to the choice of category
                               echo"<p><img src='Comedy.png' ></p>";
                           }
                           if ($catID == 'c4' ){           // image that is relevant to the choice of category
                               echo"<p><img src='Exhibition.png' ></p>";
                           }
                           if ($catID == 'c5' ){         // image that is relevant to the choice of category
                               echo"<p><img src='Festival.png' ></p>";
                           }
                           if ($catID == 'c6' ){            // image that is relevant to the choice of category
                               echo"<p><img src='Family.png' ></p>";
                           }
                           if ($catID == 'c7' ){         // image that is relevant to the choice of category
                               echo"<p><img src='Music.png' ></p>";
                           }
                           if ($catID == 'c8' ){         // image that is relevant to the choice of category
                               echo"<p><img src='Sport.png' ></p>";
                           }
                           if ($catID == 'c9' ){         // image that is relevant to the choice of category
                               echo"<p><img src='Dance.png' ></p>";
                           }
         echo"</fieldset>
        </form>";
}
$dbConn->close();
?>
</div>
</body>
</html>
</html>