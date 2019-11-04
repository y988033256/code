//@author Callum Church W15011448   
//@author Haoming Yuan W15020771

//Creating the scene
var scene = new THREE.Scene();

//Creating the camera 
var camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 ); // Perspective projection parameters
camera.position.set(0,5,15);
//Allows the scene to be controlled by the orientation on a mobile device 
var controls = new THREE.DeviceOrientationControls( camera );

var renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight); // Size of the 2D projection
document.body.appendChild(renderer.domElement); // Connecting to the canvas

//Creating the effect for the stereo rendering for VR
var effect = new THREE.StereoEffect( renderer );
effect.setSize( window.innerWidth, window.innerHeight);

//Creating the variable to load textures 
var loader = new THREE.TextureLoader();

// Define the shadow type
renderer.shadowMap.enabled = true;
renderer.shadowMap.type = THREE.PCFSoftShadowMap;

//SNOWMAN 1
// Body material, geometry and mesh 
var g1= new THREE.SphereGeometry(2, 20, 20);
var m1 = new THREE.MeshPhongMaterial( { color: 0xffffff } );
var snowman1body = new THREE.Mesh(g1, m1);
var snowman2body = new THREE.Mesh(g1, m1);

// Head material, geometry and mesh 
var g2= new THREE.SphereGeometry(1.2, 18, 18);
var m2 = new THREE.MeshPhongMaterial( { color: 0xffffff } );
var snowman1Head = new THREE.Mesh(g2, m2);
var snowman2Head = new THREE.Mesh(g2, m2);

//Eyes material, geometry and mesh 
var g3= new THREE.SphereGeometry(0.15, 18, 18);
var m3 = new THREE.MeshPhongMaterial( { color: 0x000000 } );
var snowman1Eye1 = new THREE.Mesh(g3, m3);
var snowman1Eye2= new THREE.Mesh(g3, m3);
var snowman2Eye1 = new THREE.Mesh(g3, m3);
var snowman2Eye2= new THREE.Mesh(g3, m3);

//Nose material, geometry and mesh 
var g4 = new THREE.ConeGeometry( 0.15, 1, 64 );
var m4 = new THREE.MeshPhongMaterial( { color: 0xFFA600 } );
var snowman1Nose = new THREE.Mesh( g4, m4 );
var snowman2Nose = new THREE.Mesh( g4, m4 );

//TREE
//Tree trunk material, geometry and mesh 
var gTrunk = new THREE.CylinderGeometry( 0.3, 0.3, 20, 32 );
var mTrunk = new THREE.MeshPhongMaterial( {color: 0x654321} );
var trunk = new THREE.Mesh( gTrunk, mTrunk );
var trunk2 = new THREE.Mesh( gTrunk, mTrunk );

//Positions of tree trunks
trunk.position.x = 4;
trunk.position.z = -4;
trunk2.position.x = -15;
trunk2.position.z = -2;

//Adding Tree Trunks to scene 
scene.add( trunk );
scene.add( trunk2 );

//Creating the leaves of the tree
loader.load(
    //Loading leaves texture image 
    'leaves.jpg',
    //Texture function 
    function(texture){

        //Creating the geometry for each set of leaves 
        var gSmallLeaves = new THREE.ConeBufferGeometry( 1.25, 2.5, 64 );
        var gMediumLeaves = new THREE.ConeBufferGeometry( 2.5, 5, 64 );
        var gLargeLeaves = new THREE.ConeBufferGeometry( 3.75, 7.5, 64 );

        //Mapping the texture image to the leaves 
        var mLeaves = new THREE.MeshPhongMaterial( {map:texture} );

        //Creating mesh of each set of leaves for the tree 
        var smallLeaves = new THREE.Mesh( gSmallLeaves, mLeaves );
        var mediumLeaves = new THREE.Mesh( gMediumLeaves, mLeaves );
        var largeLeaves = new THREE.Mesh( gLargeLeaves, mLeaves );

        var smallLeaves2 = new THREE.Mesh( gSmallLeaves, mLeaves );
        var mediumLeaves2 = new THREE.Mesh( gMediumLeaves, mLeaves );
        var largeLeaves2 = new THREE.Mesh( gLargeLeaves, mLeaves );

        //Tree 1 Postitioning
        smallLeaves.position.x = 4;
        smallLeaves.position.z = -4;
        smallLeaves.position.y = 10;

        mediumLeaves.position.x = 4;
        mediumLeaves.position.z = -4;
        mediumLeaves.position.y = 8;

        largeLeaves.position.x = 4;
        largeLeaves.position.z = -4;
        largeLeaves.position.y = 6;

        //Tree 2 Positioning
        smallLeaves2.position.x = -15;
        smallLeaves2.position.z = -2;
        smallLeaves2.position.y = 10;

        mediumLeaves2.position.x = -15;
        mediumLeaves2.position.z = -2;
        mediumLeaves2.position.y = 8;

        largeLeaves2.position.x = -15;
        largeLeaves2.position.z = -2;
        largeLeaves2.position.y = 6;

        //Making leaves child of trunks to help position the trees as one object 
        smallLeaves.parent = trunk;
        mediumLeaves.parent = trunk;
        largeLeaves.parent = trunk;

        smallLeaves2.parent = trunk2;
        mediumLeaves2.parent = trunk2;
        largeLeaves2.parent = trunk2;

        //Adding the leaves to the scene 
        scene.add( smallLeaves );
        scene.add( mediumLeaves );
        scene.add( largeLeaves );

        scene.add( smallLeaves2 );
        scene.add( mediumLeaves2 );
        scene.add( largeLeaves2 );
    }
);

//Snowman 1 Facial Feature Positions 
snowman1Nose.position.y = 0.15;
snowman1Nose.position.z = 1.5;
//Rotating the nose to point outwards
snowman1Nose.rotation.x = Math.PI / 2 ;

snowman1body.position.y = 1.7;
snowman1Head.position.y = 2.5;

snowman1Eye1.position.y = 0.4;
snowman1Eye1.position.x = 0.35;
snowman1Eye1.position.z = 1.1;

snowman1Eye2.position.y = 0.4;
snowman1Eye2.position.x = -0.35;
snowman1Eye2.position.z = 1.1;

//Add Snowman 1 meshes 
scene.add(snowman1body);
scene.add(snowman1Head);
scene.add(snowman1Eye1);
scene.add(snowman1Eye2);
scene.add(snowman1Nose);

//Making the facial features of the snowman a child of the head 
snowman1Eye1.parent = snowman1Head;
snowman1Eye2.parent = snowman1Head;
snowman1Nose.parent = snowman1Head;

//Making the head the child of the body
snowman1Head.parent = snowman1body;

//Snowman2 meshes added to scene 
scene.add(snowman2body);
scene.add(snowman2Head);
scene.add(snowman2Eye1);
scene.add(snowman2Eye2);
scene.add(snowman2Nose);

//Making the facial features of the snowman a child of the head
snowman2Eye1.parent = snowman2Head;
snowman2Eye2.parent = snowman2Head;
snowman2Nose.parent = snowman2Head;
snowman2Head.parent = snowman2body;

//Snowman 2 Positions
snowman2Nose.position.y = 0.15;
snowman2Nose.position.z = 1.5;
//Rotating the nose to point outwards 
snowman2Nose.rotation.x = Math.PI / 2 ;

snowman2body.position.y = 1.7;
snowman2body.position.x = -10;
snowman2body.position.z = -15;

snowman2Head.position.y = 2.5;

snowman2Eye1.position.y = 0.4;
snowman2Eye1.position.x = 0.35;
snowman2Eye1.position.z = 1.1;

snowman2Eye2.position.y = 0.4;
snowman2Eye2.position.x = -0.35;
snowman2Eye2.position.z = 1.1;

// Adding a spotlight to the scene 
var spotLight = new THREE.SpotLight(0xffffff);
spotLight.position.set(-0, 30, 60);
spotLight.intensity = 1.22;
scene.add(spotLight);

// Set the shadow quality
spotLight.castShadow = true;
spotLight.shadow.mapSize.width = 512;
spotLight.shadow.mapSize.height = 512;
spotLight.shadow.camera.near = 0.5;
spotLight.shadow.camera.far = 500;
spotLight.shadow.radius = 5.0;


//Geometry, Material and Mesh array for snow 
var geoArray = [];
var matArray = [];
var meshArray = [];
//Number of snow particles to produce 
var iNumber = 4000;
//position array 
var posInititalArray = [];
//Direction array 
var dirArray = [];

// Create the particles
for (var i=0; i<iNumber; i++)
{
    //Creating the geometry for the each snow particle 
    geoArray.push(new THREE.SphereGeometry(0.03, 5, 5));
    //Creating the material for the snow particles 
    matArray.push(new THREE.MeshBasicMaterial( {color: 0xffffff, transparent: true, opacity: 0.8} ));
    //Creating mesh for the snow particles  
    meshArray.push(new THREE.Mesh(geoArray[i], matArray) );

    // For snow and rain
    meshArray[i].position.y = 15 + Math.random()*10;
    meshArray[i].position.x = Math.random()*60 - 20;
    meshArray[i].position.z = -40+Math.random()*65 ;

    // Backup initial position
    posInititalArray.push(new THREE.Vector3() );
    posInititalArray[i].x = meshArray[i].position.x;
    posInititalArray[i].y = meshArray[i].position.y;
    posInititalArray[i].z = meshArray[i].position.z;
    
    //Adding snow to the scene 
    scene.add(meshArray[i]);
}

//Creating the wave geometry for the floor 
function wave(geometry, cycle, height) {
for (var i = 0; i < geometry.vertices.length; i++) {
    const width = geometry.parameters.width/2;
    const xPos = ((geometry.vertices[i].x*cycle) / width)*(Math.PI);
    // compute z-pos using sine function
    var zPos = Math.sin(xPos)*height;
    geometry.vertices[i].z = zPos;
}
    geometry.verticesNeedUpdate = true;
    geometry.computeVertexNormals();
}

//Creating the variables for the scene box 
var plane = null;
var wall1 = null;
var wall2 = null;
var wall3 = null;
var wall4 = null;
var sky = null;


// load a resource
loader.load(
    // resource URL
    'snowfloor.jpg',
    // Function when resource is loaded
    function ( texture ) {
        // do something with the texture
         var material = new THREE.MeshBasicMaterial( { map: texture} );
         texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
         texture.repeat.set(5, 5 );
         texture.offset.set( 0.5, 0.5 );

         planeGeom = new THREE.PlaneGeometry(100, 100,150,150);
         plane = new THREE.Mesh(planeGeom,material);
         plane.rotation.x = -Math.PI/2;
         plane.position.y = -2;
         plane.material.side = THREE.DoubleSide;    
         console.log(planeGeom.parameters.width); 
         scene.add(plane);
         wave(planeGeom, 35, 0.3);

    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

//wall1
loader.load(
    // resource URL
    'px.jpg',
    // Function when resource is loaded
    function ( texture ) {
        // Creating the material, geometry and mesh for the wall
         var material = new THREE.MeshBasicMaterial( { map: texture} );
         wall1Geom = new THREE.PlaneGeometry(100, 100);
         wall1 = new THREE.Mesh(wall1Geom,material);
      
         wall1.material.side = THREE.DoubleSide;    
         console.log(wall1Geom.parameters.width); 
         scene.add(wall1);
          wall1.position.z = -50;
          wall1.position.y = 47;
      
    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);


//wall2
loader.load(
    // resource URL
    'nx.jpg',
    // Function when resource is loaded
    function ( texture ) {
        // Creating the material, geometry and mesh for the wall
         var material = new THREE.MeshBasicMaterial( { map: texture} );
         wall2Geom = new THREE.PlaneGeometry(100, 100);
         wall2 = new THREE.Mesh(wall2Geom,material);
      
         wall2.material.side = THREE.DoubleSide;    
         console.log(wall2Geom.parameters.width); 
         scene.add(wall2);
         wall2.rotation.y = Math.PI*1.5;
         wall2.position.y = 47;
         wall2.position.x = 50;

      
    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

//wall3
loader.load(
    // resource URL
    'pz.jpg',
    // Function when resource is loaded
    function ( texture ) {
        // Creating the material, geometry and mesh for the wall
         var material = new THREE.MeshBasicMaterial( { map: texture} );
         wall3Geom = new THREE.PlaneGeometry(100, 100);
         wall3 = new THREE.Mesh(wall3Geom,material);
      
         wall3.material.side = THREE.DoubleSide;    
         console.log(wall3Geom.parameters.width); 
         scene.add(wall3);        
          wall3.rotation.y = 9.444;
       
          wall3.position.z = 49;
          wall3.position.y = 47;
      
    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);


//wall4
loader.load(
    // resource URL
    'nz.jpg',
    // Function when resource is loaded
    function ( texture ) {
        // Creating the material, geometry and mesh for the wall
         var material = new THREE.MeshBasicMaterial( { map: texture} );
         wall4Geom = new THREE.PlaneGeometry(100, 100);
         wall4 = new THREE.Mesh(wall4Geom,material);
      
         wall4.material.side = THREE.DoubleSide;    
         console.log(wall4Geom.parameters.width); 
         scene.add(wall4);
         wall4.rotation.y = Math.PI/2;
         wall4.position.y = 47;
         wall4.position.x = -50;

      
    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

// sky
loader.load(
    // resource URL
    'sky.jpg',
    // Function when resource is loaded
    function ( texture ) {
        // Creating the material, geometry and mesh for the sky
         var material = new THREE.MeshBasicMaterial( { map: texture} );
         skyGeom = new THREE.PlaneGeometry(100, 100);
         sky = new THREE.Mesh(skyGeom,material);
         sky.rotation.x = -Math.PI/2;
         sky.position.y = 95;
         sky.material.side = THREE.DoubleSide;    
         console.log(skyGeom.parameters.width); 
         scene.add(sky);
     
      
    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

//Creation of explosion properties (Haoming Yuan)

//Explosion geometry, material and mesh variables
var exgeoArray = [];
var exmatArray = [];
var exmeshArray = [];
//Number of particles involved in the explosion
var exNumber = 100;
//Explosion position array
var exposInititalArray = [];
//Explosion direction array
var exdirArray = [];

//Loop creates the particles to the amount of the exNumber
 for (var i=0; i<exNumber; i++)
{
    //Create the geometry, material and mesh for the explosion particles 
    exgeoArray.push(new THREE.SphereGeometry(0.1, 5, 5));
    exmatArray.push(new THREE.MeshBasicMaterial( {color: 0xFF0000, transparent: true, opacity: 0.3} ));
    exmeshArray.push(new THREE.Mesh(exgeoArray[i], exmatArray) );
      
    // Explosion particles positioning 
    exmeshArray[i].position.x = 0;
    exmeshArray[i].position.y = 30;
    exmeshArray[i].position.z = 0;
    exdirArray.push(new THREE.Vector3() );
    exdirArray[i].x = Math.random() * 0.5 - 0.25;
    exdirArray[i].y = Math.random() * 0.5 - 0.25;
    exdirArray[i].z = Math.random() * 0.5 - 0.25;
    

    // Backup position
    exposInititalArray.push(new THREE.Vector3() );
    exposInititalArray[i].x = exmeshArray[i].position.x;
    exposInititalArray[i].y = exmeshArray[i].position.y;
    exposInititalArray[i].z = exmeshArray[i].position.z;
    
    //Adds explosion particles to the scene 
    scene.add(exmeshArray[i]); 
}

//User Interaction (Group)

//Adding eventListener for use of the keyboard being pressed down 
document.addEventListener('keydown', keyPressed, false);
//When the key is pressed down...
function keyPressed(e){
  //Switch checking if the condition is true or false
  switch(e.key) {
    //The case that ArrowUp is pressed the head rotates upwards
    case 'ArrowUp':
        snowman1Head.rotateX(-0.1);
        break;
    //The case that ArrowDown is pressed the head rotates downwards
    case 'ArrowDown':
        snowman1Head.rotateX(0.1);
        break;
    //The case that ArrowLeft is pressed the head rotates left
    case 'ArrowLeft':
        snowman1Head.rotateY(-0.1);
        break;
    //The case that ArrowLeft is pressed the head rotates right
    case 'ArrowRight':
        snowman1Head.rotateY(0.1);
        break;
    //The case that 5 is pressed the body rotates left
    case '5':
        snowman2body.rotateY(-0.1);
    break;
    //The case that 6 is pressed the body rotates right
    case '6':
        snowman2body.rotateY(0.1);
    break;
    //The case that 8 is pressed the explosion animation functoin is called (Haoming Yuan)
    case '8':
         exanimate();             
    break;
    //The case that 9 is pressed the below materials have the color changed (Haoming Yuan)
    case '9':
      m5.color.set(0x000000);  
      m1.color.set(0x000000);   
      m2.color.set(0x000000); 
      m6.color.set(0x000000); 
      m3.color.set(0xffffff);
      m7.color.set(0xffffff);
      m8.color.set(0xffffff); 
      m10.color.set(0xffffff);      
    break;
    
  }
 //prevents the browser from doing default actions when the button is pressed
 e.preventDefault();
}
  
//Adding eventListener for when the key is released 
document.addEventListener("keyup", onDocumentKeyup, false);
function onDocumentKeyup(o){
  //Switch checking if the condition is true or false
  switch(o.key) {
    //The case that ArrowUp is pressed the head rotates upwards
    case '9':
       m5.color.set(0xffffff); 
       m1.color.set(0xffffff); 
       m2.color.set(0xffffff); 
       m6.color.set(0xffffff); 
       m3.color.set(0x000000);
       m7.color.set(0x000000);
       m8.color.set(0x000000);  
       m10.color.set(0x000000);         
    break;
  }
  //prevents the browser from doing default actions when the button is pressed
  o.preventDefault(); 
}


//Windmill Axis mesh, geometry and material (Callum Church)
var windaxisG = new THREE.CylinderGeometry( 0.5, 0.5, 1, 32 );
var windaxisM = new THREE.MeshPhongMaterial( {color: 0xf2f2f2} );
var windmillAxis = new THREE.Mesh( windaxisG, windaxisM );

//Adds windmillAxis to the scene 
scene.add( windmillAxis );

//Windmill Base Texture 
loader.load(
    'bricks.jpg',
    function(texture){

        //Creating the windmill base geometry, material and mesh 
        var windbaseG = new THREE.CylinderGeometry( 3, 5, 13, 32 );
        var windbaseM = new THREE.MeshBasicMaterial( {map:texture} );
        var windmillBase = new THREE.Mesh( windbaseG, windbaseM );

        //Adding the windmill base to the scene 
        scene.add( windmillBase );

        //Positioning the windmill base 
        windmillBase.position.x = 15;
        windmillBase.position.y = 5;
        windmillBase.position.z = -15;
        windmillBase.rotation.y = -0.4;

        //Making the windmillAxis a child of the windmillBase
        windmillAxis.parent = windmillBase;
    }

);

//Callum Church Individual Work - windmill wing texture and build 
loader.load(
    // resource URL
    'wood.jpg',
    // Function when resource is loaded
    function ( texture ) {
        // creating the geometry and materials for the propellors 
        var propellorGeometry = new THREE.BoxGeometry( 2, 5, 0.2 );
        var propellorMaterial = new THREE.MeshBasicMaterial( { map: texture} );
        //The below materials have a reduced opacity to create the blur effect
        var propellorMaterialB1 = new THREE.MeshBasicMaterial( { transparent:true, map: texture, opacity:0.5} );
        var propellorMaterialB2 = new THREE.MeshBasicMaterial( { transparent:true, map: texture, opacity:0.3} );

        //Creating the mesh for the main propellors 
        var propellor1 = new THREE.Mesh( propellorGeometry, propellorMaterial );
        var propellor2 = new THREE.Mesh( propellorGeometry, propellorMaterial );
        var propellor3 = new THREE.Mesh( propellorGeometry, propellorMaterial );

        //Creating the mesh for the first blur propellor 
        var propellor1Blur1 = new THREE.Mesh( propellorGeometry, propellorMaterialB1 );
        var propellor2Blur1 = new THREE.Mesh( propellorGeometry, propellorMaterialB1 );
        var propellor3Blur1 = new THREE.Mesh( propellorGeometry, propellorMaterialB1 );

        //Creating the mesh for the second blurred propellor 
        var propellor1Blur2 = new THREE.Mesh( propellorGeometry, propellorMaterialB2 );
        var propellor2Blur2 = new THREE.Mesh( propellorGeometry, propellorMaterialB2 );
        var propellor3Blur2 = new THREE.Mesh( propellorGeometry, propellorMaterialB2 );
      
        //Adding all propellor meshes to the scene 
        scene.add( propellor1 );
        scene.add( propellor2 );
        scene.add( propellor3 );
        scene.add( propellor1Blur1 );
        scene.add( propellor1Blur2 );
        scene.add( propellor2Blur1 );
        scene.add( propellor2Blur2 );
        scene.add( propellor3Blur1 );
        scene.add( propellor3Blur2 );

        //All propellors made children of the windmillAxis so they rotate when the axis rotates 
        propellor1.parent = windmillAxis;
        propellor2.parent = windmillAxis;
        propellor3.parent = windmillAxis;
        propellor1Blur1.parent = windmillAxis;
        propellor2Blur1.parent = windmillAxis;
        propellor3Blur1.parent = windmillAxis;
        propellor1Blur2.parent = windmillAxis;
        propellor2Blur2.parent = windmillAxis;
        propellor3Blur2.parent = windmillAxis;

        //Propellor one positioning
        propellor1.position.x = 0;
        propellor1.position.y = 0.3;
        propellor1.position.z = 2;
        propellor1.rotation.x = Math.PI / 2 ;
        
        //Blurred propellors positioned and angled slightly away from main propellor for blur 
        propellor1Blur1.position.x = -0.2;
        propellor1Blur1.position.y = 0.28;
        propellor1Blur1.position.z = 2;
        propellor1Blur1.rotation.x = Math.PI / 2 ;   
        propellor1Blur1.rotation.z = 0.2 ;

        propellor1Blur2.position.x = -0.5;
        propellor1Blur2.position.y = 0.29;
        propellor1Blur2.position.z = 2;
        propellor1Blur2.rotation.x = Math.PI / 2 ;   
        propellor1Blur2.rotation.z = 0.2 ;          
        
        //Propellor2 positioning
        propellor2.position.x = -1.8;
        propellor2.position.y = 0.32;
        propellor2.position.z = -1;
        propellor2.rotation.x = Math.PI / 2 ;
        propellor2.rotation.z = Math.PI / 1.5 ;
        //Blurred propellors positioned and angled slightly away from main propellor for blur 
        propellor2Blur1.position.x = -1.5;
        propellor2Blur1.position.y = 0.28;
        propellor2Blur1.position.z = -1.2;
        propellor2Blur1.rotation.x = Math.PI / 2 ;
        propellor2Blur1.rotation.z = Math.PI / 1.4 ;
        propellor2Blur2.position.x = -1.2;
        propellor2Blur2.position.y = 0.27;
        propellor2Blur2.position.z = -1.4;
        propellor2Blur2.rotation.x = Math.PI / 2 ;
        propellor2Blur2.rotation.z = Math.PI / 1.4 ;

        //Propellor3 positioning
        propellor3.position.x = 1.8;
        propellor3.position.y = 0.31;
        propellor3.position.z = -1;
        propellor3.rotation.x = Math.PI / 2 ;
        propellor3.rotation.z = Math.PI / -1.5 ;
        //Blurred propellors positioned and angled slightly away from main propellor for blur 
        propellor3Blur1.position.x = 1.8;
        propellor3Blur1.position.y = 0.28;
        propellor3Blur1.position.z = -0.5;
        propellor3Blur1.rotation.x = Math.PI / 2 ;
        propellor3Blur1.rotation.z = Math.PI / -1.6 ;
        propellor3Blur2.position.x = 1.8;
        propellor3Blur2.position.y = 0.27;
        propellor3Blur2.position.z = -0.3;
        propellor3Blur2.rotation.x = Math.PI / 2 ;
        propellor3Blur2.rotation.z = Math.PI / -1.6 ;

    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

//Positioning of the axis
windmillAxis.position.x = 0;
windmillAxis.position.y = 2;
windmillAxis.position.z = 4; 
windmillAxis.rotation.x = Math.PI / 2 ;

var iFrame = 0;

var idex;

//Function for the animation of the explosion (Haoming Yuan)
function exanimate()
{
    //Requests the animation function 
    idex = requestAnimationFrame(exanimate);
     // Move the explosion particles
    for (var i=0; i<exNumber; i++)
    {
        
        // Explosion repositioning for animation 
        exmeshArray[i].position.x = exmeshArray[i].position.x + exdirArray[i].x;
        exmeshArray[i].position.y = exmeshArray[i].position.y + exdirArray[i].y;
        exmeshArray[i].position.z = exmeshArray[i].position.z + exdirArray[i].z;

        //Restarts the explosion and brings it back to initial positioning
        if (iFrame%90 == 0) 
        {             
            exmeshArray[i].position.x = 0;
            exmeshArray[i].position.y = 30;
            exmeshArray[i].position.z = 0;
            cancelAnimationFrame(idex);
        }      
    }    
}

//Animation Function
function animate() 
{

    //The rotation rate of windmillAxis 
    windmillAxis.rotation.y +=0.5;
    
    //requests the animation function
    requestAnimationFrame(animate);

    //Constantly update the controls for the mobile orientation 
    controls.update();
    
    // Move the particles
    for (var i=0; i<iNumber; i++)
    {    
        
        // Snow repositioning for animation 
        meshArray[i].position.y = meshArray[i].position.y - 0.04;
        meshArray[i].position.x = posInititalArray[i].x + Math.sin(iFrame/50 + i);
        meshArray[i].position.z = posInititalArray[i].z + Math.sin(iFrame/50 + i);
        //If the snow passes y=0 it resets back to y=10
        if (meshArray[i].position.y < 0)
        {
            meshArray[i].position.y = 10;
        }
        
    }    
    //Updates the scene to animate 
    iFrame++;
    //Run render function 
    render();
}

//Render function
function render() {
      //Applies the effect of stereo-rendering 
      effect.render(scene, camera);
}

//Runs animation function 
animate();