<!DOCTYPE html>
<html lang="en">
<head>
    <link  rel="stylesheet" type="text/css" href="index.css"/>
    <meta charset="UTF-8">
    <title>Admin</title>
</head>
<body>
<div class="header">
    <p>Add Event</p>
</div>
<div class="navbar">
    <ul>
        <li><a href="index.html">Home</a></li>
        <li><a href="viewEventsPage.php">View events</a></li>
        <li><a href="admin.php">Admin</a></li>
        <li><a href="Credits.html">Credits</a></li>
        <li><a href="addEventForm.php">Add Event</a></li>
    </ul>
</div>
<div class="form">
    <?php
    include 'database_conn.php';
    $venueName = isset($_REQUEST['venueName'])?$_REQUEST['venueName']:null;     // Prevent undefined index error notice messages following submission of the form
    $catDesc = isset($_REQUEST['catDesc'])?$_REQUEST['catDesc']:null;           //Prompt the user to enter data / make a choice if they do not do so for a required field
                                                                                // the form link to addecent.php when add new event i will get to the page
    echo"<form method='post' action='addEvent.php'>
         <fieldset>
           <legend><h2>Please enter the detail</h2></legend>
             <p>Information must be entered in the field that have *</p>
             <p><label>Title* </label><input type='text' name='eventTitle'</p>";        // field for enter event title

    $venuesql = "SELECT venueID,venueName FROM AE_venue";                    // sql for dynamically generated from database content
    $venuequeryResult = $dbConn->query($venuesql);                           //with one option for each of the categories and venues
    if($venuequeryResult === false){
        echo "<p>Query failed: ".$dbConn->error."</p>\n";
        exit;
    }
    echo"<p><label>Venue*</label><select name='VenueID'>";       // sql for dynamically generated from database content
    while ($venuerowObj = $venuequeryResult->fetch_object())     //with one option for each of the categories and venues
    {
        $venueID = $venuerowObj->venueID;
        $venueName = $venuerowObj->venueName;
        echo"<option value='$venueID'>$venueName</option></div>\n";
    }
    echo"</select></p>";

    $catsql = "SELECT catID,catDesc FROM AE_category";                  // sql for dynamically generated from database content
    $catqueryResult = $dbConn->query($catsql);                          //with one option for each of the categories and venues

    if($catqueryResult === false){
        echo "<p>Query failed: ".$dbConn->error."</p>\n";
        exit;
    }

    echo"<p><label>Category* </label><select name='catID'>";      // field for enter category
    while ($catrowObj = $catqueryResult->fetch_object())
    {
        $catID = $catrowObj->catID;
        $catDesc = $catrowObj->catDesc;
        echo"<option value='$catID'>$catDesc</option></div>\n";
    }
    echo"</select></p>";                                           // field for enter event Start Date, event End Date, event Price and description
    echo"<p><label> Start Date* </label><input type='text' placeholder='DD-MM-YY' name='eventStartDate'></p>              
                 <p><label> End Date* </label><input type='text' placeholder='DD-MM-YY' name='eventEndDate'></p>          
                 <p><label> Price(£)</label><input type='text' name='eventPrice'></p>           
                 <p>Description</p>
                 <p><textarea name='eventDescription' style='width:63%; height:150px; font-family: Calibri; font-size:15px;'></textarea></p>
                 <input type='submit' value='Add Event' />
            </fieldset>
        </form>";

$catqueryResult->close();
$venuequeryResult->close();
$dbConn->close();
?>
</div>
</body>
</html>
