function showMyData(){

     var displayResources = $("#display-resources");
     var values = [];
     var values2 = [];
     var values3 = [];
     var values4 = [];
     var values5 = [];
     var values6 = [];
     var name = [];

     var td2 = document.getElementById('td2');
   
 
     $.ajax({
         'async': false,
         'global': false,
         'url': "/Chart.json",
         'dataType': "json",
         "type": "GET",
         'success': function (data) {
              for (var i in data){
              
                 
             
                name.push(Object.keys(data[i]));
 
                 values.push(data[0]);
                 values2.push(data[2]); 
                 values3.push(data[3]); 
                 values4.push(data[4]); 
                 values5.push(data[5]); 
                 values6.push(data[6]); 
              
         }
         var text = document.createTextNode(data[1][0]);
         td2.appendChild(text);
   
         console.log(data);  
         console.log(values);  
         console.log(values2); 
         console.log(values3);
         console.log(values4);
         console.log(values5);
         console.log(values6); 
             displayResources.html("values","values2","values3","values4","values5","values6","name");
   
         }
         
     });
 
 
 
     var h1 = Highcharts.chart('container1', {
        chart: {
        
          
            height: 400
        },
         title: {
             text: 'Datarate Values'
         },
     
         subtitle: {
            
         },
     
         yAxis: {
             title: {
                 text: "data rate"
             }
         },
     
         xAxis: {
             type: 'datetime',
             accessibility: {
                 rangeDescription: 'E-Link'
             }
         },
     
         legend: {
             layout: 'vertical',
             align: 'right',
             verticalAlign: 'middle'
         },
     
         plotOptions: {
             series: {
                 label: {
                     connectorAllowed: false
                 },
                 pointStart: Date.now()
             }
         },
     
         series: [ {
             name: "dataRate",
             data: values[0]
         }],
         credits: {
            enabled: false
          },
     
         responsive: {
             rules: [{
                 condition: {
                     maxWidth: 500
                 },
                 chartOptions: {
                     legend: {
                         layout: 'horizontal',
                         align: 'center',
                         verticalAlign: 'bottom'
                     }
                 }
             }]
         }
     
     });
     
     
 
 
     var h3 = Highcharts.chart('container3', {
        
        credits: {
            enabled: false
          },
        
         title: {
             text: 'Blockrate Values:'
         },
     
         subtitle: {
           
         },
     
         yAxis: {
             title: {
                 text: "block rate"
             }
         },
     
         xAxis: {
            type: 'datetime',
             accessibility: {
                 rangeDescription: 'E-Link'
             }
         },
     
         legend: {
             layout: 'vertical',
             align: 'right',
             verticalAlign: 'middle'
         },
     
         plotOptions: {
             series: {
                 label: {
                     connectorAllowed: false
                 },
                 pointStart: Date.now()
             }
         },
     
         series: [  {
             name: "blockRate",
             data: values2[0]
         }],
     
         responsive: {
             rules: [{
                 condition: {
                     maxWidth: 500
                 },
                 chartOptions: {
                     legend: {
                         layout: 'horizontal',
                         align: 'center',
                         verticalAlign: 'bottom'
                     }
                 }
             }]
         }
     
     });
     
     
     var h4 = Highcharts.chart('container4', {

        credits: {
            enabled: false
          },
        
        title: {
            text: 'Chunkrate Values'
        },
    
        subtitle: {
           
        },
    
        yAxis: {
            title: {
                text: "chunk rate"
            }
        },
    
        xAxis: {
            type: 'datetime',
            accessibility: {
                rangeDescription: 'E-Link'
            }
        },
    
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle'
        },
    
        plotOptions: {
            series: {
                label: {
                    connectorAllowed: false
                },
                pointStart: Date.now()
            }
        },
    
        series: [ {
            name: "chunkRate",
            data: values3[0]
        }],
    
        responsive: {
            rules: [{
                condition: {
                    maxWidth: 500
                },
                chartOptions: {
                    legend: {
                        layout: 'horizontal',
                        align: 'center',
                        verticalAlign: 'bottom'
                    }
                }
            }]
        }
    
    });
    
    
    var h5 = Highcharts.chart('container5', {

        credits: {
            enabled: false
          },
        
        title: {
            text: 'Buffer Events Values'
        },
    
        subtitle: {
           
        },
    
        yAxis: {
            title: {
                text: "buffer events"
            }
        },
    
        xAxis: {
            type: 'datetime',
            accessibility: {
                rangeDescription: 'E-Link'
            }
        },
    
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle'
        },
    
        plotOptions: {
            series: {
                label: {
                    connectorAllowed: false
                },
                pointStart: Date.now()
            }
        },
    
        series: [ {
            name: "buffer events",
            data: values4[0]
        }],
    
        responsive: {
            rules: [{
                condition: {
                    maxWidth: 500
                },
                chartOptions: {
                    legend: {
                        layout: 'horizontal',
                        align: 'center',
                        verticalAlign: 'bottom'
                    }
                }
            }]
        }
    
    });
    
    
    var h6 = Highcharts.chart('container6', {

        credits: {
            enabled: false
          },
        
        title: {
            text: 'Interrupts Values'
        },
    
        subtitle: {
           
        },
    
        yAxis: {
            title: {
                text: "interrupts"
            }
        },
    
        xAxis: {
            type: 'datetime',
            accessibility: {
                rangeDescription: 'E-Link'
            }
        },
    
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle'
        },
    
        plotOptions: {
            series: {
                label: {
                    connectorAllowed: false
                },
                pointStart: Date.now()
            }
        },
    
        series: [ {
            name: "interrupts",
            data: values5[0]
        }],
    
        responsive: {
            rules: [{
                condition: {
                    maxWidth: 500
                },
                chartOptions: {
                    legend: {
                        layout: 'horizontal',
                        align: 'center',
                        verticalAlign: 'bottom'
                    }
                }
            }]
        }
    
    });
    
    
    var h7 = Highcharts.chart('container7', {

        credits: {
            enabled: false
          },
        
        title: {
            text: 'Polls Values'
        },
    
        subtitle: {
           
        },
    
        yAxis: {
            title: {
                text: "polls"
            }
        },
    
        xAxis: {
            type: 'datetime',
            accessibility: {
                rangeDescription: 'E-Link'
              
            }
            
        },
    
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle'
        },
    
        plotOptions: {
            series: {
                label: {
                    connectorAllowed: false
                },
                pointStart: Date.now()
            }
        },
    
        series: [ {
            name: "polls",
            data: values6[0]
        }],
    
        responsive: {
            rules: [{
                condition: {
                    maxWidth: 500
                },
                chartOptions: {
                    legend: {
                        layout: 'horizontal',
                        align: 'center',
                        verticalAlign: 'bottom'
                    }
                }
            }]
        }
    
    });
    
    
 
 return h1,h3,h4,h5,h6,h7;
 
 }
 
 
 $(function() {
    
      index = 0,
     
  
    $('#interval-start').bind('click', function() {

         
     "use strict";
     var milliseconds = 1;
     var seconds = 1000;
     var minutes = 60 * seconds;
     var hours = 60 * minutes;
     var days = 24 * hours;
      interval = setInterval(function() {
       
        var td2 = document.getElementById('td2');
        var values_time = [];
       
        var values2_time = [];
        var values3_time = [];
        var values4_time = [];
        var values5_time = [];
        var values6_time = [];
        $.ajax({
          type: 'GET',
          crossDomain: true,
          'url': "/Chart.json",
      
          success: function(data) {
            for (var i in data){


                values_time.push(data[0]);
               
                values2_time.push(data[2]);
                values3_time.push(data[3]);
                values4_time.push(data[4]);
                values5_time.push(data[5]);
                values6_time.push(data[6]);
               
             } 
             var text = document.createTextNode(data[1][0]);
             td2.innerHTML = "";
             td2.append(text);
            $('#container1').highcharts({    
                credits: {
                    enabled: false
                  },      
              title: {
                text: "DataRate Values"
              },
              yAxis: {
                title: {
                  text: 'data rate',
                  useHTML: true,
                  style: {
                    "-webkit-transform": "rotate(90deg)",
                    "-moz-transform": "rotate(90deg)",
                    "-o-transform": "rotate(90deg)"
                  }
                }
              },
              xAxis: {
                  type: 'datetime',
                
                    accessibility: {
                        rangeDescription: 'E-Link'
                      
                    }
                    
                },
            
                plotOptions: {
                    series: {
                        label: {
                            connectorAllowed: false
                        },
                        pointStart: Date.now()
                    }
                },
            
              series: [ {
                name: "dataRate",
                data: values_time[0]
            }]
        });
        $('#container3').highcharts({
            credits: {
                enabled: false
              },
          
            title: {
              text: 'BlockRate Values'
            },
            yAxis: {
              title: {
                text: 'block rate',
                useHTML: true,
                style: {
                  "-webkit-transform": "rotate(90deg)",
                  "-moz-transform": "rotate(90deg)",
                  "-o-transform": "rotate(90deg)"
                }
              }
            },
            xAxis: {
                type: 'datetime',
                  accessibility: {
                      rangeDescription: 'E-Link'
                    
                  }
                  
              },
          
              plotOptions: {
                  series: {
                      label: {
                          connectorAllowed: false
                      },
                      pointStart: Date.now()
                  }
              },
          
            series: [ {
              name: "blockRate",
              data: values2_time[0]
          }]
      });
      $('#container4').highcharts({

        credits: {
            enabled: false
          },
          
        title: {
          text: 'ChunkRate Values' 
        },
        yAxis: {
          title: {
            text: 'chunk rate',
            useHTML: true,
            style: {
              "-webkit-transform": "rotate(90deg)",
              "-moz-transform": "rotate(90deg)",
              "-o-transform": "rotate(90deg)"
            }
          }
        },
        xAxis: {
            type: 'datetime',
              accessibility: {
                  rangeDescription: 'E-Link'
                
              }
              
          },
      
          plotOptions: {
              series: {
                  label: {
                      connectorAllowed: false
                  },
                  pointStart: Date.now()
              }
          },
      
        series: [ {
          name: "chunkRate",
          data: values3_time[0]
      }]
  });
  $('#container5').highcharts({

    credits: {
        enabled: false
      },

    title: {
      text: 'Buffer Events Values'
    },
    yAxis: {
      title: {
        text: 'buffer events',
        useHTML: true,
        style: {
          "-webkit-transform": "rotate(90deg)",
          "-moz-transform": "rotate(90deg)",
          "-o-transform": "rotate(90deg)"
        }
      }
    },
    xAxis: {
        type: 'datetime',
          accessibility: {
              rangeDescription: 'E-Link'
            
          }
          
      },
  
      plotOptions: {
          series: {
              label: {
                  connectorAllowed: false
              },
              pointStart: Date.now()
          }
      },
  
    series: [ {
      name: "buffer events",
      data: values4_time[0]
  }]
});
$('#container6').highcharts({

    credits: {
        enabled: false
      },

                
          
    title: {
      text: 'Interrupts Values'
    },
    yAxis: {
      title: {
        text: 'interrupts',
        useHTML: true,
        style: {
          "-webkit-transform": "rotate(90deg)",
          "-moz-transform": "rotate(90deg)",
          "-o-transform": "rotate(90deg)"
        }
      }
    },
    xAxis: {
        type: 'datetime',
          accessibility: {
              rangeDescription: 'E-Link'
            
          }
          
      },
  
      plotOptions: {
          series: {
              label: {
                  connectorAllowed: false
              },
              pointStart: Date.now()
          }
      },
  
    series: [ {
      name: "interrupts",
      data: values5_time[0]
  }]
});
$('#container7').highcharts({

    credits: {
        enabled: false
      },

                
          
    title: {
      text: 'Polls Values'
    },
    yAxis: {
      title: {
        text: 'polls',
        useHTML: true,
        style: {
          "-webkit-transform": "rotate(90deg)",
          "-moz-transform": "rotate(90deg)",
          "-o-transform": "rotate(90deg)"
        }
      }
    },
    xAxis: {
        type: 'datetime',
          accessibility: {
              rangeDescription: 'E-Link'
            
          }
          
      },
  
      plotOptions: {
          series: {
              label: {
                  connectorAllowed: false
              },
              pointStart: Date.now()
          }
      },
  
    series: [ {
      name: "polls",
      data: values6_time[0]
  }]
});
        //here comes the new highchart

    },
    error: function() {
      console.log('error');
    }
  });
        index++;
      }, (5 * seconds));
    });
  });
  
 $(document).ready(function() {
     
   
   
     var byte_prefix = 'short';
     math.createUnit('B', { prefixes: byte_prefix, aliases: ['byte']}, {override: true});
     math.createUnit('Blocks', { definition: '1024 bytes', prefixes: byte_prefix });
     math.createUnit('Chunks', { prefixes: byte_prefix });
   
     Highcharts.setOptions({
       // This is for all plots, change Date axis to local timezone
       global : {
         useUTC : false
       }
     })
     showMyData();
 
 });   
 
 
 