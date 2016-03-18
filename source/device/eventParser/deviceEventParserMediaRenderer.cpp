
#include <raumkernel/device/eventParser/deviceEventParserMediaRenderer.h>
#include <raumkernel/manager/managerEngineer.h>

namespace Raumkernel
{
    namespace Devices
    {
        namespace EventParser
        {
            DeviceEventParserMediaRenderer::DeviceEventParserMediaRenderer() : DeviceEventParser()
            {
            }


            DeviceEventParserMediaRenderer::~DeviceEventParserMediaRenderer()
            {
            }


            bool DeviceEventParserMediaRenderer::isRoomOnline(std::string _roomUDN)
            {
                return getManagerEngineer()->getZoneManager()->isRoomOnline(_roomUDN);
            }


            void DeviceEventParserMediaRenderer::propertyChangedAvTransportProxy(std::string _xml)
            {            
                Devices::MediaRenderer *mediaRenderer = (Devices::MediaRenderer*)device;
                bool anyStateChanged = false, avTransportUriValueChanged = false, currentTrackMetadataChanged = false, transportStateChanged = false;
                bool roomTransitionStateChanged = false;
 
                logDebug("A property on AvTransport proxy has changed (Device: " + mediaRenderer->getUDN() + ")", CURRENT_POSITION);
           
                // get a copy of the media renderer state structure. we will change the data and set it back again by copy
                Devices::MediaRendererState rendererState = mediaRenderer->state();

                // save xml on state so we can always update the parsing.
                // This seems not to be necessary but due the RF-Kernel adds disabled renderers to subscription states it could be
                // that we do have to update the rendereState when the device list changes (if renderer is not already available in the renderer list and his state has changed to online)
                rendererState.avTransportProxySubscXmlData = _xml;

                try
                {
                    // try to get the "instance" node in the subscription xml. The child nodes of this node are our data we want to have
                    rapidxml::xml_node<> *instanceNode = getInstanceNodeFromXML(_xml);
                    if (!instanceNode)
                    {
                        logError("Error parsing XML subscription from device: " + mediaRenderer->getUDN(), CURRENT_POSITION);
                        return;
                    }

                    rendererState.aVTransportURI = getNodeVal(instanceNode, "AVTransportURI", rendererState.aVTransportURI, avTransportUriValueChanged);
                    rendererState.aVTransportURIMetaData = getNodeVal(instanceNode, "AVTransportURIMetaData", rendererState.aVTransportURIMetaData, anyStateChanged);
                    rendererState.currentTrackURI = getNodeVal(instanceNode, "CurrentTrackURI", rendererState.currentTrackURI, anyStateChanged);
                    rendererState.currentTrackMetaData = getNodeVal(instanceNode, "CurrentTrackMetaData", rendererState.currentTrackMetaData, currentTrackMetadataChanged);
                    rendererState.contentType = getNodeVal(instanceNode, "ContentType", rendererState.contentType, anyStateChanged);
                    rendererState.currentTrack = Tools::NumUtil::toUInt32(getNodeVal(instanceNode, "CurrentTrack", std::to_string(rendererState.currentTrack), anyStateChanged));
                    rendererState.numberOfTracks = Tools::NumUtil::toUInt32(getNodeVal(instanceNode, "NumberOfTracks", std::to_string(rendererState.numberOfTracks), anyStateChanged));
                    rendererState.currentTrackDuration = Tools::DateUtil::timeStringToTimeMS(getNodeVal(instanceNode, "CurrentTrackDuration", Tools::DateUtil::timeMSToTimeString(rendererState.currentTrackDuration), anyStateChanged));
                    rendererState.bitrate = Tools::NumUtil::toUInt32(getNodeVal(instanceNode, "Bitrate", std::to_string(rendererState.bitrate), anyStateChanged));                                        
                    rendererState.transportState = Devices::ConversionTool::stringToTransportState(getNodeVal(instanceNode, "TransportState", Devices::ConversionTool::transportStateToString(rendererState.transportState), transportStateChanged));
                    rendererState.roomTransportStatesCombined = getNodeVal(instanceNode, "RoomStates", rendererState.roomTransportStatesCombined, roomTransitionStateChanged);          
                    rendererState.playMode = Devices::ConversionTool::stringToPlayMode(getNodeVal(instanceNode, "CurrentPlayMode", Devices::ConversionTool::playModeToString(rendererState.playMode), roomTransitionStateChanged));

                    // get the information if any of the states has changed
                    anyStateChanged = anyStateChanged || avTransportUriValueChanged || currentTrackMetadataChanged || transportStateChanged || roomTransitionStateChanged;

                    // when the room state changes we have to update the room states map. The combined value consists of the roomUDNs and the transport states 
                    if (roomTransitionStateChanged && !rendererState.roomTransportStatesCombined.empty())
                    {           
                        std::vector<std::string> foundUDNs;
                        auto roomStateInfo = Tools::StringUtil::explodeString(rendererState.roomTransportStatesCombined, ",");                        
                        // run through each info block which looks something like "RoomUDN=TransportState"
                        for (auto &roomStateString : roomStateInfo)
                        {
                            auto roomStateInfoParts = Tools::StringUtil::explodeString(roomStateString, "=");
                            if (roomStateInfoParts.size() >= 2)
                            {
                                std::string roomUDN = Tools::CommonUtil::formatUDN(roomStateInfoParts[0]);                            
                                MediaRenderer_TransportState roomTransportState = Devices::ConversionTool::stringToTransportState(roomStateInfoParts[1]);   

                                foundUDNs.emplace_back(roomUDN);

                                // we have to update the transport state on the room state map.
                                // if the state for the room does not exists we create it first 
                                if (rendererState.roomStates.find(roomUDN) == rendererState.roomStates.end())
                                {
                                    MediaRendererRoomState newEmptyRoomState;
                                    rendererState.roomStates.insert(std::make_pair(roomUDN, newEmptyRoomState));
                                }
                                rendererState.roomStates[roomUDN].roomUDN = roomUDN;
                                rendererState.roomStates[roomUDN].transportState = roomTransportState;
                                // a room state may be delivered by the subscription even if the room is offline                               
                                rendererState.roomStates[roomUDN].online = isRoomOnline(roomUDN);
                            }                            
                           
                        }  

                        // Remove rooms which are not listed from the room states!
                        rendererState.removeNonReferredRoomStates(foundUDNs);

                    }                                 

                    // if the AvTransport uri has changed we have to checl if the new uri is a container or only a link
                    // if its a container the "rendererState.containerId" will be filled, otherwise it will be empty
                    if (avTransportUriValueChanged)
                    {
                        auto uri = LUrlParser::clParseURL::ParseURL(rendererState.aVTransportURI);                               
                        auto queryKeyValues = Tools::UriUtil::parseQueryString(uri.m_Query); 

                        // if there is a "cid" key the current loaded items are from a container 
                        // the container value is escaped but the "parseQueryString" Method has done the unescaping for us
                        auto it = queryKeyValues.find("cid");
                        rendererState.containerId = (it != queryKeyValues.end()) ? it->second : "";        
                    }

                    // TODO: create the current media item from the "CurrentTrackMetaData" value (this is necessary for non list/query playlists)                    
                    if (currentTrackMetadataChanged)
                    {
                        // TODO: @@@              
                        if (!rendererState.currentTrackMetaData.empty())
                        {
                            Media::MediaItemCreator mediaItemCreator;
                            mediaItemCreator.setLogObject(getLogObject());
                            rendererState.currentMediaItem = mediaItemCreator.createMediaItemFromTrackMetadata(rendererState.currentTrackMetaData);
                        }
                        else
                        {
                            rendererState.currentMediaItem = nullptr;
                        }
                        
                    }


                }
                catch (Raumkernel::Exception::RaumkernelException &e)
                {
                    if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                        throw e;
                    logError(e.what(), CURRENT_FUNCTION);
                }
                catch (std::exception &e)
                {
                    logError(e.what(), CURRENT_FUNCTION);
                }
                catch (std::string &e)
                {
                    logError(e, CURRENT_FUNCTION);
                }
                catch (OpenHome::Exception &e)
                {
                    logError(e.Message(), CURRENT_FUNCTION);
                }
                catch (...)
                {
                    logError("Unknown Exception", CURRENT_FUNCTION);
                }

                // update the new state of the renderer
                mediaRenderer->setState(rendererState);

                // TODO: emit some signal.... maybe from the device manager? 
                // or from the media renderer which will signal the device manager which will signal again?
            }


            void DeviceEventParserMediaRenderer::propertyChangedRenderingControlProxy(std::string _xml)
            {         
                //Example XML
                /* 
                <Event xmlns="urn:schemas-upnp-org:metadata-1-0/RCS/">
                <InstanceID val="0">
                <RoomVolumes val="uuid:e1104a23-2493-498c-8c44-49ba8d1810d8=44,uuid:6e395fd9-f326-41c6-b8b3-eed1897923e6=0" />
                <Volume channel="Master" val="22" />
                <RoomMutes val="uuid:e1104a23-2493-498c-8c44-49ba8d1810d8=0,uuid:6e395fd9-f326-41c6-b8b3-eed1897923e6=0" />
                </InstanceID>
                </Event>
                */

                Devices::MediaRenderer *mediaRenderer = (Devices::MediaRenderer*)device;
                bool anyStateChanged = false, volumeStateChanged = false, muteStateChanged;

                logDebug("A property on RenderingControl proxy has changed (Device: " + mediaRenderer->getUDN() + ")", CURRENT_POSITION);

                // get a copy of the media renderer state structure. we will change the data and set it back again by copy
                Devices::MediaRendererState rendererState = mediaRenderer->state();

                // save xml on state so we can always update the parsing.
                // This seems not to be necessary but due the RF-Kernel adds disabled renderers to subscription states it could be
                // that we do have to update the rendereState when the device list changes (if renderer is not already available in the renderer list and his state has changed to online)
                rendererState.renderingControlSubscXmlData = _xml;

                try
                {
                    // try to get the "instance" node in the subscription xml. The child nodes of this node are our data we want to have
                    rapidxml::xml_node<> *instanceNode = getInstanceNodeFromXML(_xml);
                    if (!instanceNode)
                    {
                        logError("Error parsing XML subscription from device: " + mediaRenderer->getUDN(), CURRENT_POSITION);
                        return;
                    }
                    
                    rendererState.volume = Tools::NumUtil::toUInt32(getNodeVal(instanceNode, "Volume", std::to_string(rendererState.volume), anyStateChanged));
                    rendererState.mute = Tools::CommonUtil::toBool(getNodeVal(instanceNode, "Mute", std::to_string(rendererState.mute), anyStateChanged));
                    rendererState.roomMuteStatesCombined = getNodeVal(instanceNode, "RoomMutes", rendererState.roomMuteStatesCombined, muteStateChanged);
                    rendererState.roomVolumeStatesCombined = getNodeVal(instanceNode, "RoomVolumes", rendererState.roomVolumeStatesCombined, volumeStateChanged);

                    anyStateChanged = anyStateChanged || muteStateChanged || volumeStateChanged;                                                  

                    // when the room volume state changes we have to update the room states map. The combined value consists of the roomUDNs and the volume value
                    if (volumeStateChanged && !rendererState.roomVolumeStatesCombined.empty())
                    {            
                        std::vector<std::string> foundUDNs;
                        auto roomStateInfo = Tools::StringUtil::explodeString(rendererState.roomVolumeStatesCombined, ",");                     
                        for (auto &roomStateString : roomStateInfo)
                        {                         
                            auto roomStateInfoParts = Tools::StringUtil::explodeString(roomStateString, "=");
                            if (roomStateInfoParts.size() >= 2)
                            {
                                std::string roomUDN = Tools::CommonUtil::formatUDN(roomStateInfoParts[0]);                                                             
                                std::uint8_t volume = (std::uint8_t)Tools::NumUtil::toUInt32(roomStateInfoParts[1]);   

                                foundUDNs.emplace_back(roomUDN);

                                // we have to update the volume on the room state map.
                                // if the state for the room does not exists we create it first 
                                if (rendererState.roomStates.find(roomUDN) == rendererState.roomStates.end())
                                {
                                    MediaRendererRoomState newEmptyRoomState;
                                    rendererState.roomStates.insert(std::make_pair(roomUDN, newEmptyRoomState));
                                }
                                rendererState.roomStates[roomUDN].roomUDN = roomUDN;
                                rendererState.roomStates[roomUDN].volume = volume;
                                // a room state may be delivered by the subscription even if the room is offline                               
                                rendererState.roomStates[roomUDN].online = isRoomOnline(roomUDN);                                
                            }
                        }  

                        // Remove rooms which are not listed from the room states!
                        rendererState.removeNonReferredRoomStates(foundUDNs);
                    }

                    // when the room mute state changes we have to update the room states map. The combined value consists of the roomUDNs and the mute state
                    if (muteStateChanged && !rendererState.roomMuteStatesCombined.empty())
                    {
                        std::vector<std::string> foundUDNs;
                        auto roomStateInfo = Tools::StringUtil::explodeString(rendererState.roomMuteStatesCombined, ","); 
                        for (auto &roomStateString : roomStateInfo)
                        {                            
                            auto roomStateInfoParts = Tools::StringUtil::explodeString(roomStateString, "=");
                            if (roomStateInfoParts.size() >= 2)
                            {
                                std::string roomUDN = Tools::CommonUtil::formatUDN(roomStateInfoParts[0]);
                                bool mute = Tools::CommonUtil::toBool(roomStateInfoParts[1]);
                               
                                foundUDNs.emplace_back(roomUDN);
                                
                                // we have to update the mute state on the room state map.
                                // if the state for the room does not exists we create it first 
                                if (rendererState.roomStates.find(roomUDN) == rendererState.roomStates.end())
                                {
                                    MediaRendererRoomState newEmptyRoomState;
                                    rendererState.roomStates.insert(std::make_pair(roomUDN, newEmptyRoomState));
                                }
                                rendererState.roomStates[roomUDN].roomUDN = roomUDN;
                                rendererState.roomStates[roomUDN].mute = mute;   
                                rendererState.roomStates[roomUDN].online = isRoomOnline(roomUDN);
                            }
                        }

                        // Remove rooms which are not listed from the room states!
                        rendererState.removeNonReferredRoomStates(foundUDNs);
                    } 

                   

                    // now calculate and update the overall mute state on the zone itself. The zone may be muted fully or only partially
                    MediaRenderer_MuteState overallMuteState;
                    bool minOneRoomMuted = false, allRoomsMuted = true;                    

                    for (auto &roomState : rendererState.roomStates)
                    { 
                        // only check online room states for the overall mute status
                        if (roomState.second.online)
                        {
                            minOneRoomMuted = minOneRoomMuted || roomState.second.mute;
                            allRoomsMuted = allRoomsMuted && roomState.second.mute;
                        }
                    }                   
                
                    if (rendererState.mute || (allRoomsMuted && minOneRoomMuted))
                        overallMuteState = MediaRenderer_MuteState::MRPMUTE_ALL;
                    else if (minOneRoomMuted)
                        overallMuteState = MediaRenderer_MuteState::MRPMUTE_PARTIAL;
                    else
                        overallMuteState = MediaRenderer_MuteState::MRPMUTE_NONE;    

                    rendererState.muteState = overallMuteState;


                }
                catch (Raumkernel::Exception::RaumkernelException &e)
                {
                    if (e.type() == Raumkernel::Exception::ExceptionType::EXCEPTIONTYPE_APPCRASH)
                        throw e;
                    logError(e.what(), CURRENT_FUNCTION);
                }
                catch (std::exception &e)
                {
                    logError(e.what(), CURRENT_FUNCTION);
                }
                catch (std::string &e)
                {
                    logError(e, CURRENT_FUNCTION);
                }
                catch (OpenHome::Exception &e)
                {
                    logError(e.Message(), CURRENT_FUNCTION);
                }
                catch (...)
                {
                    logError("Unknown Exception", CURRENT_FUNCTION);
                }

                // update the new state of the renderer
                mediaRenderer->setState(rendererState);
            }

        }
    }
}
