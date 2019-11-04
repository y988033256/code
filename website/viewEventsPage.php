<!doctype html>
<html lang="en">
<head>
    <link  rel="stylesheet" type="text/css" href="index.css"/>
    <meta charset="UTF-8" />
    <title>View Event</title>
</head>
<body>
<div class="header">
    <p>View Event</p>
</div>
<div class="navbar">
    <ul>
        <li><a href="index.html">Home</a></li>
        <li><a href="viewEventsPage.php">View events</a></li>
        <li><a href="admin.php">Admin</a></li>
        <li><a href="Credits.html">Credits</a></li>
        <li><a href="wireframe.docx">WireFrame</a></li>
    </ul>
</div>
<?php
include 'database_conn.php';      // make db connection

$sql = "SELECT eventTitle, eventDescription,venueName,catDesc, eventStartDate,eventEndDate, eventPrice
        FROM AE_events 
        INNER JOIN AE_category 
        ON AE_category.catID = AE_events.catID    
        INNER JOIN AE_venue
        ON AE_venue.venueID = AE_events. venueID
        ORDER BY eventTitle";
                                                  // Construct an SQL query
$queryResult = $dbConn->query($sql);       // Execute the query and store the result set


if($queryResult === false)
{
    echo "<p>Query failed: ".$dbConn->error."</p>";
    exit;
}
else
    {
        echo "<div class='EventTitle'>  
   
                  <span class='Title'>Title</span>
                  <span class='Description'>Description</span>
                  <span class='Venue'>Venue</span>
                  <span class='Category'>Category</span>
                  <span class='SDate'>Start Date</span>
                  <span class='EDate'>End Date</span>
                  <span class='EventPrice'>Price(£)</span>
                  
              </div>\n";

        while($rowObj = $queryResult->fetch_object())     //Iterate over that result set Extract each record  and Display it

        {
            $eventTitle = $rowObj->eventTitle;
            $eventDescription = $rowObj->eventDescription;
            $venueName = $rowObj->venueName;
            $catDesc = $rowObj->catDesc;
            $eventStartDate = $rowObj->eventStartDate;
            $eventEndDate = $rowObj->eventEndDate;
            $eventPrice = $rowObj->eventPrice;
                                                                   // display all the detail of the events
            echo "<div class='Event'>          

                      <span class='Title'>$eventTitle</span>   
                      <span class='Description'>$eventDescription</span>
                      <span class='Venue'>$venueName</span>
                      <span class='Category'>$catDesc</span>
                      <span class='SDate'>$eventStartDate</span>
                      <span class='EDate'>$eventEndDate</span>
                      <span class='EventPrice'>$eventPrice</span>
                      
                   </div>\n";
        }
    }
$queryResult->close();
$dbConn->close();
?>
</body>
</html>


