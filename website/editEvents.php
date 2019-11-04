<!DOCTYPE html>
<html lang="en">
<head>
    <link  rel="stylesheet" type="text/css" href="index.css"/>
    <meta charset="UTF-8">
    <title>Admin</title>
</head>
<body>
<div class="header">
    <p>Edit Event</p>
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
    include 'database_conn.php';      // make db connection
    $eventID = isset($_REQUEST['eventID'])?$_REQUEST['eventID']:null;               // Prevent undefined index error notice messages following submission of the form
    $Venue = isset($_REQUEST['Venue'])?$_REQUEST['Venue']:null;
    $Category = isset($_REQUEST['Category'])?$_REQUEST['Category']:null;

    $SQL ="SELECT eventID,eventTitle, eventDescription,venueName,catDesc, eventStartDate,eventEndDate, eventPrice
           FROM AE_events
           INNER JOIN AE_category
           ON AE_category.catID = AE_events.catID
           INNER JOIN AE_venue
           ON AE_venue.venueID = AE_events. venueID
           WHERE eventID = $eventID";                        //Construct an SQL query
    $queryResult = $dbConn->query($SQL);
    if($queryResult === false)
    {
        echo "<p>Query failed: ".$dbConn->error."</p>";
        exit;
    }
    $rowObj = $queryResult->fetch_object();                   // the form for edit the event link to updateevent.php when press update will go to the update page
    echo "<form method='post' action='updateEvent.php'>
                <fieldset>
                        <legend><h2>Event detail<input type='hidden' name='eventID' value= '$eventID'></h2></legend>     
                        <p><label>Title: </label><input type='text' name='eventTitle'  value='{$rowObj->eventTitle}'></p>";

    echo"<p><label>Venue:</label><select name='Venuename'>
          <option>{$rowObj->venueName}</option>";
    $venuesql = "SELECT venueID,venueName FROM AE_venue WHERE venueName != '{$rowObj->venueName}'";   //  with this sql the option wont have duplicate
    $venuequeryResult = $dbConn->query($venuesql);                   //sql for the option to get the data from database
    if($venuequeryResult === false)
    {
        echo "<p>Query failed: ".$dbConn->error."</p>";              //Venue to choose created dynamically from the database records using PHP
        exit;
    }
    while ($venuerowObj = $venuequeryResult->fetch_object())
    {
        $venueName = $venuerowObj->venueName;
            echo "<option value='$venueName' >$venueName</option>\n";
    }
    echo"</select></p>";

    echo"<p><label>Category: </label><select name='catDesc'>";
    echo" <option selected='selected'>{$rowObj->catDesc}</option>";
    $catsql = "SELECT catDesc FROM AE_category WHERE catDesc != '{$rowObj->catDesc}'";                  //  with this sql the option wont have duplicate
    $catqueryResult = $dbConn->query($catsql);                    //  Initially display the current values for the event title,
    if($catqueryResult === false)                                 //  description, start date, end date, price, category and venue
    {                                                             //  with the category and venue as the default values in pre-defined
        echo "<p>Query failed: ".$dbConn->error."</p>";           //  lists that are dynamically generated from database content with
        exit;                                                     //  one option for each of the categories and venues, respectively, in the database.
    }

    while ($catrowObj = $catqueryResult->fetch_object())
    {
        $catDesc = $catrowObj->catDesc;
        echo "<option value='$catDesc'>$catDesc</option></div>\n";
    }
    echo"</select></p>";
    echo"<p><label>Start Date: </label><input type='text' name='eventStartDate'value='{$rowObj->eventStartDate}'></p>";  // current values for start date also can enter data in
    echo"<p><label>End Date: </label><input type='text' name='eventEndDate'value='{$rowObj->eventEndDate}'></p>";       // current values for end date also can enter data in
    echo"<p><label>Price(£): </label><input type='text' name='eventPrice' value='{$rowObj->eventPrice}'></p>";            // current values for event price also can enter data in
    echo"<p>Description</p>
        <p><textarea name='eventDescription'style='width:63%; height:120px; font-family: Calibri; font-size:15px;'>{$rowObj->eventDescription}</textarea></p>
        <input type='submit' value='Update' />
        </fieldset>
        </form>";                                // current values for event Description also can enter data in
    $catqueryResult->close();
    $venuequeryResult->close();
    $dbConn->close();
    ?>
</div>
</body>
</html>
