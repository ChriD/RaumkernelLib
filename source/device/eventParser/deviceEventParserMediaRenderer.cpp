
#include <raumkernel/device/eventParser/deviceEventParserMediaRenderer.h>

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


            void DeviceEventParserMediaRenderer::propertyChangedAvTransportProxy(std::string _xml)
            {            
                Devices::MediaRenderer *mediaRenderer = (Devices::MediaRenderer*)device;
                bool anyStateChanged = false, avTransportUriValueChanged = false, currentTrackMetadataChanged = false;
 
                logDebug("A property on AvTransport proxy has changed (Device: " + mediaRenderer->getUDN() + ")", CURRENT_POSITION);
           
                // get a copy of the media renderer state structure. we will change the data and set it back again by copy
                Devices::MediaRendererState rendererState = mediaRenderer->state();

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

                    // TODO: 
                    // TransportState
                    // RoomStates 

                    // TODO: @@@

                    anyStateChanged = anyStateChanged || avTransportUriValueChanged || currentTrackMetadataChanged;


                    // TODO: create the current media item from the "CurrentTrackMetaData" value (this is necessary for non list playlists)
                    if (currentTrackMetadataChanged)
                    {
                    }

                    // TODO: handle AVTranportUri (set contaniner id to state & get media list for zone when changed and i zone renderer)
                    if (avTransportUriValueChanged)
                    {
                    }

                    // TODO: handle room states

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
                // orf from the media renderer which will signal the device manager which will signal again?



                // TODO::
                // * lock this method
                // * create the information objects from the xml
                // * lock the device lists from the device manager
                // * update the information objects on the devivce itself
                // * unlock the device lists from the device manager
                // * unlock this method


            }


            /*

            std::string propertyXML = "", attributeString = "", curentTrackMetadata = "", contentType = "", aVTransportURIMetaData = "", aVTransportURI = "", currentTrackURI = "", currentTrackDuration = "", propChangeInfo = "";
            std::string uriQuery;
            boost::uint32_t currentTrackDurationMS = 0, currentTrack = 0, numberOfTracks = 0, bitrate = 0;
            MediaRendererTransportState transportState;
            xml_document<> doc;
            xml_node<> *eventNode, *instanceNode, *valueNode;
            xml_attribute<> *attribute;
            bool someStateChanged = false;
            bool avTransportUriChanged = false;


            char* cstr = new char[propertyXML.size() + 1];
            strcpy(cstr, propertyXML.c_str());
            doc.parse<0>(cstr);

            eventNode = doc.first_node("Event", 0, false);
            if (!eventNode)
            {
            this->Log(LogType::LOGERROR, "RenderingService on '" + this->GetIdentificationString() + "': 'Event' node in propertyXML not found!", __FUNCTION__);
            return;
            }

            instanceNode = eventNode->first_node("InstanceId", 0, false);
            if (!instanceNode)
            {
            this->Log(LogType::LOGERROR, "RenderingService on '" + this->GetIdentificationString() + "': 'InstanceId' node in propertyXML not found!", __FUNCTION__);
            return;
            }

            try
            {

            boost::mutex::scoped_lock scoped_lock(mutexRendererState);

            valueNode = instanceNode->first_node("CurrentTrackMetaData", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            curentTrackMetadata = attribute->value();
            if (mediaRendererState.currentTrackMetaData != curentTrackMetadata)
            {
            mediaRendererState.currentTrackMetaData = curentTrackMetadata;
            someStateChanged = true;
            AddPropChangeInfo("CurrentTrackMetaData", propChangeInfo);

            // parse into mediaItem track class
            currentMediaItem = managerList.contentManager->CreateMediaItemFromCurrentTrackMetadata(curentTrackMetadata);
            }
            }

            valueNode = instanceNode->first_node("ContentType", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            contentType = attribute->value();
            if (mediaRendererState.contentType != contentType)
            {
            mediaRendererState.contentType = contentType;
            someStateChanged = true;
            AddPropChangeInfo("ContentType", propChangeInfo);
            }
            }

            valueNode = instanceNode->first_node("AVTransportURI", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            aVTransportURI = attribute->value();
            if (mediaRendererState.aVTransportURI != aVTransportURI)
            {
            mediaRendererState.aVTransportURI = aVTransportURI;

            // in some cases it may be that the avTransportUri es empty

            if (!aVTransportURI.empty())
            {
            // we have to handle the query values of the AVTransportUri.
            // In case we wan't to play eg. Track 5 of a list, we have to use the cid(containerId) of the container the renderer has set currently
            // so this is the place where the actual cid is set to the 'mediaRendererState' structure
            boost::network::uri::uri instance(aVTransportURI);
            uriQuery = instance.query();

            // parse the query string for all id and value pairs it may have
            boost::unordered_map<std::string, std::string> queryValues = Utils::ParseQueryString(uriQuery);

            // now handle the cid(containerId) information. if its there, then get it and store it
            boost::unordered_map<std::string, std::string>::iterator it = queryValues.find("cid");
            if (it != queryValues.end())
            {
            std::string containerIdEncoded = it->second;
            // we want to store the unescaped value due the cid will be escaped again on bending AVTransport Uri
            // UPDATE: no need to Unescape the values! This is already done by 'ParseQueryString'
            //mediaRendererState.containerId = Utils::Unescape(containerIdEncoded);
            mediaRendererState.containerId = containerIdEncoded;
            }
            else
            mediaRendererState.containerId = "";

            // TODO: handle fid && fii

            someStateChanged = true;
            avTransportUriChanged = true;
            AddPropChangeInfo("AVTransportURI", propChangeInfo);

            }
            }
            }

            valueNode = instanceNode->first_node("AVTransportURIMetaData", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            aVTransportURIMetaData = attribute->value();
            if (mediaRendererState.aVTransportURIMetaData != aVTransportURIMetaData)
            {
            mediaRendererState.aVTransportURIMetaData = aVTransportURIMetaData;
            someStateChanged = true;
            AddPropChangeInfo("AVTransportURIMetaData", propChangeInfo);
            }
            }

            valueNode = instanceNode->first_node("CurrentTrackURI", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            currentTrackURI = attribute->value();
            if (mediaRendererState.currentTrackURI != currentTrackURI)
            {
            mediaRendererState.currentTrackURI = currentTrackURI;
            someStateChanged = true;
            AddPropChangeInfo("CurrentTrackURI", propChangeInfo);
            }
            }

            valueNode = instanceNode->first_node("CurrentTrackDuration", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            currentTrackDuration = attribute->value();
            currentTrackDurationMS = Utils::TimeStringToTimeMS(currentTrackDuration);
            if (mediaRendererState.currentTrackDuration != currentTrackDuration)
            {
            mediaRendererState.currentTrackDuration = currentTrackDuration;
            mediaRendererState.currentTrackDurationMS = currentTrackDurationMS;
            someStateChanged = true;
            AddPropChangeInfo("CurrentTrackDuration", propChangeInfo);
            }
            }

            valueNode = instanceNode->first_node("CurrentTrack", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            attributeString = attribute->value();
            currentTrack = this->toInt(attributeString);
            if (mediaRendererState.currentTrack != currentTrack)
            {
            mediaRendererState.currentTrack = currentTrack;
            someStateChanged = true;
            AddPropChangeInfo("CurrentTrack", propChangeInfo);
            }
            }

            valueNode = instanceNode->first_node("NumberOfTracks", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            attributeString = attribute->value();
            numberOfTracks = this->toInt(attributeString);
            if (mediaRendererState.numberOfTracks != numberOfTracks)
            {
            mediaRendererState.numberOfTracks = numberOfTracks;
            someStateChanged = true;
            AddPropChangeInfo("NumberOfTracks", propChangeInfo);
            }

            }

            valueNode = instanceNode->first_node("Bitrate", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            attributeString = attribute->value();
            bitrate = this->toInt(attributeString);
            if (mediaRendererState.bitrate != bitrate)
            {
            mediaRendererState.bitrate = bitrate;
            someStateChanged = true;
            AddPropChangeInfo("Bitrate", propChangeInfo);
            }
            }

            valueNode = instanceNode->first_node("TransportState", 0, false);
            if (valueNode)
            {
            attribute = valueNode->first_attribute("val");
            attributeString = attribute->value();
            transportState = StringToMediaRendererTransportState(attributeString);
            if (mediaRendererState.transportState != transportState)
            {
            mediaRendererState.transportState = transportState;
            someStateChanged = true;
            AddPropChangeInfo("TransportState", propChangeInfo);
            }
            }

            valueNode = instanceNode->first_node("RoomStates", 0, false);
            if (valueNode)
            {
            std::vector<std::string> roomVolumeStringVector;
            std::vector<std::string> roomStringVector;
            std::string roomUDN;
            MediaRendererTransportState	roomTransportState;
            MediaRendererRoomState roomState;

            attribute = valueNode->first_attribute("val");
            attributeString = attribute->value();

            if (!attributeString.empty())
            {

            roomVolumeStringVector = Utils::ExplodeString(attributeString, ",");

            for (auto &roomString : roomVolumeStringVector)
            {
            roomStringVector = Utils::ExplodeString(roomString, "=");
            if (roomStringVector.size() > 1)
            {
            roomUDN = Utils::FormatUDN(roomStringVector[0]);
            roomTransportState = StringToMediaRendererTransportState(roomStringVector[1]);

            if (roomStateMap.find(roomUDN) != roomStateMap.end())
            {
            roomState = roomStateMap.at(roomUDN);
            roomStateMap.erase(roomUDN);
            }

            roomState.roomUDN = roomUDN;
            if (roomState.transportState != roomTransportState)
            {
            roomState.transportState = roomTransportState;
            someStateChanged = true;
            AddPropChangeInfo("RoomStates", propChangeInfo);
            }

            roomStateMap.insert(std::make_pair(roomUDN, roomState));
            }
            }
            }

            }
            }
            catch (OpenHome::Exception &ex)
            {
            this->UPNPException(ex, __FUNCTION__);
            }
            catch (std::exception &ex)
            {
            this->Log(LogType::LOGERROR, ex.what(), __FUNCTION__);
            }
            catch (...)
            {
            this->Log(LogType::LOGERROR, "Unknown Error", __FUNCTION__);
            }

            // if soemthing has changed we do signal the subscribers
            if (someStateChanged)
            {
            // each update of the zones we generate and store a random number
            // this is needed for JSON webserver for long polling action on zone information
            boost::uint32_t curUpdateId = Utils::GetRandomNumber();
            if (managerList.deviceManager->GetLastUpdateIdRendererState() == curUpdateId)
            curUpdateId++;
            managerList.deviceManager->SetLastUpdateIdRendererState(curUpdateId);

            // start loading the playlist for the renderer. Virtual Renderer UDN = virtual Zone UDN
            if (avTransportUriChanged)
            managerList.contentManager->StartGetMediaItemListByZoneUDN(this->GetUDN(), false);

            this->Log(LogType::LOGDEBUG, "Properties Changed: " + propChangeInfo + " (" + this->GetIdentificationString() + ")", __FUNCTION__);
            signalMediaRendererStateChanged(this->UDN);
            }*/

            void DeviceEventParserMediaRenderer::propertyChangedRenderingControlProxy(std::string _xml)
            {         
                Devices::MediaRenderer *mediaRenderer = (Devices::MediaRenderer*)device;

                logDebug("A property on RenderingControl proxy has changed (Device: " + mediaRenderer->getUDN() + ")", CURRENT_POSITION);


                // TODO: 
                // Volume
                // RoomVolumes 
                // Mute
                // RoomMutes


                // TODO::
                // * lock this method
                // * create the information objects from the xml
                // * lock the device lists from the device manager
                // * update the information objects on the devivce itself
                // * unlock the device lists from the device manager
                // * unlock this method
            }

            /*

            // Example XML

            /*
            <Event xmlns="urn:schemas-upnp-org:metadata-1-0/RCS/">
            <InstanceID val="0">
            <RoomVolumes val="uuid:e1104a23-2493-498c-8c44-49ba8d1810d8=44,uuid:6e395fd9-f326-41c6-b8b3-eed1897923e6=0" />
            <Volume channel="Master" val="22" />
            <RoomMutes val="uuid:e1104a23-2493-498c-8c44-49ba8d1810d8=0,uuid:6e395fd9-f326-41c6-b8b3-eed1897923e6=0" />
            </InstanceID>
            </Event>
            */


            /*
            std::string propertyXML = "", attributeString = "", propChangeInfo = "";
            xml_document<> doc;
            xml_node<> *eventNode, *instanceNode, *roomVolumesNode, *volumeNode, *muteNode, *roomMutesNode;
            xml_attribute<> *attribute;
            boost::uint8_t masterVolume = mediaRendererState.volume, masterMute = 0;
            MediaRendererMuteState masterMuteState = mediaRendererState.muteState;
            bool minOneRoomMuted = false, allRoomsMuted = true, someStateChanged = false;;
            boost::unordered_map<std::string, MediaRendererRoomState>	roomStateMapLocal;

            this->Log(LogType::LOGDEBUG, "RenderingService on '" + this->GetIdentificationString() + "': property changed!", __FUNCTION__);

            this->GetRenderingControlProxy()->PropertyLastChange(propertyXML);

            // this xml vontains the proprty values for the rendering ervice which normaly are 'volume level' and 'mute state'
            // in this case for rooms and the zone (master)

            if (propertyXML.empty())
            {
            this->Log(LogType::LOGWARNING, "RenderingService on '" + this->GetIdentificationString() + "': property changed has no XML!", __FUNCTION__);
            return;
            }

            // add lock because ware are going on to update our lists
            boost::mutex::scoped_lock scoped_lock(mutexRendererState);


            char* cstr = new char[propertyXML.size() + 1];
            strcpy(cstr, propertyXML.c_str());
            doc.parse<0>(cstr);

            eventNode = doc.first_node("Event", 0, false);
            if (!eventNode)
            {
            this->Log(LogType::LOGERROR, "RenderingService on '" + this->GetIdentificationString() + "': 'Event' node in propertyXML not found!", __FUNCTION__);
            return;
            }

            instanceNode = eventNode->first_node("InstanceId", 0, false);
            if (!instanceNode)
            {
            this->Log(LogType::LOGERROR, "RenderingService on '" + this->GetIdentificationString() + "': 'InstanceId' node in propertyXML not found!", __FUNCTION__);
            return;
            }

            //this->GetDeviceManager()->LockRendererServerListForUpdate(true);

            try
            {

            volumeNode = instanceNode->first_node("Volume", 0, false);
            if (volumeNode)
            {
            attribute = volumeNode->first_attribute("val");
            attributeString = attribute->value();
            masterVolume = this->toInt(attributeString);
            }

            roomVolumesNode = instanceNode->first_node("RoomVolumes", 0, false);
            if (roomVolumesNode)
            {
            std::vector<std::string> roomVolumeStringVector;
            std::vector<std::string> roomStringVector;
            std::string roomUDN, roomVolume;
            MediaRendererRoomState roomState;

            // volume node value looks like this "uuid:e1104a23-2493-498c-8c44-49ba8d1810d8=44,uuid:6e395fd9-f326-41c6-b8b3-eed1897923e6=0"
            // it consists of the room uid and the volume value
            attribute = roomVolumesNode->first_attribute("val");
            attributeString = attribute->value();

            roomVolumeStringVector = Utils::ExplodeString(attributeString, ",");

            for (auto &roomString : roomVolumeStringVector)
            {
            roomStringVector = Utils::ExplodeString(roomString, "=");
            if (roomStringVector.size() >= 2)
            {
            roomUDN = Utils::FormatUDN(roomStringVector[0]);
            roomVolume = roomStringVector[1];

            if (roomStateMapLocal.find(roomUDN) != roomStateMapLocal.end())
            {
            roomState = roomStateMapLocal.at(roomUDN);
            roomStateMapLocal.erase(roomUDN);
            }

            roomState.roomUDN = roomUDN;
            roomState.volume = this->toInt(roomVolume);

            roomStateMapLocal.insert(std::make_pair(roomUDN, roomState));
            }
            }

            }

            roomMutesNode = instanceNode->first_node("RoomMutes", 0, false);
            if (roomMutesNode)
            {
            std::vector<std::string> roomMuteStringVector;
            std::vector<std::string> roomStringVector;
            std::string roomUDN, roomMute;
            MediaRendererRoomState roomState;

            // mute node value looks like this "uuid:e1104a23-2493-498c-8c44-49ba8d1810d8=1,uuid:6e395fd9-f326-41c6-b8b3-eed1897923e6=0"
            // it consists of the room uid and the volume value
            attribute = roomMutesNode->first_attribute("val");
            attributeString = attribute->value();

            roomMuteStringVector = Utils::ExplodeString(attributeString, ",");

            for (auto &roomString : roomMuteStringVector)
            {
            roomStringVector = Utils::ExplodeString(roomString, "=");
            if (roomStringVector.size() >= 2)
            {

            roomUDN = Utils::FormatUDN(roomStringVector[0]);
            roomMute = roomStringVector[1];

            if (roomStateMapLocal.find(roomUDN) != roomStateMapLocal.end())
            {
            roomState = roomStateMapLocal.at(roomUDN);
            roomStateMapLocal.erase(roomUDN);
            }

            roomState.roomUDN = roomUDN;
            roomState.mute = this->toInt(roomMute) != 0;

            if (roomState.mute)
            minOneRoomMuted = true;
            else
            allRoomsMuted = false;

            roomStateMapLocal.insert(std::make_pair(roomUDN, roomState));
            }
            }

            if (allRoomsMuted && minOneRoomMuted)
            masterMuteState = MediaRendererMuteState::MRPMUTE_ALL;
            else if (minOneRoomMuted)
            masterMuteState = MediaRendererMuteState::MRPMUTE_PARTIAL;
            else
            masterMuteState = MediaRendererMuteState::MRPMUTE_NONE;

            }

            muteNode = instanceNode->first_node("Mute", 0, false);
            if (muteNode)
            {
            attribute = muteNode->first_attribute("val");
            attributeString = attribute->value();
            masterMute = this->toInt(attributeString);
            if (masterMute == 1)
            masterMuteState = MediaRendererMuteState::MRPMUTE_ALL;
            else if (minOneRoomMuted)
            masterMuteState = MediaRendererMuteState::MRPMUTE_PARTIAL;
            else
            masterMuteState = MediaRendererMuteState::MRPMUTE_NONE;
            }




            someStateChanged = false;

            // check change of value and signal those ones (to deviceManager, and this one signals out to whatever has attached to the signal)
            if (mediaRendererState.volume != masterVolume)
            {
            mediaRendererState.volume = masterVolume;
            someStateChanged = true;
            AddPropChangeInfo("Volume", propChangeInfo);
            }
            if (mediaRendererState.muteState != masterMuteState)
            {
            mediaRendererState.muteState = masterMuteState;
            someStateChanged = true;
            AddPropChangeInfo("Mute", propChangeInfo);
            }

            // update room states
            MediaRendererRoomState roomStateLocal, roomState;

            for (auto &mapItem : roomStateMapLocal)
            {
            roomStateLocal = (MediaRendererRoomState)mapItem.second;

            if (roomStateMap.find(roomStateLocal.roomUDN) != roomStateMap.end())
            {
            roomState = roomStateMap.at(roomStateLocal.roomUDN);
            roomStateMap.erase(roomStateLocal.roomUDN);
            }

            if (roomState.roomUDN != roomStateLocal.roomUDN)
            {
            roomState.roomUDN = roomStateLocal.roomUDN;
            someStateChanged = true;
            AddPropChangeInfo("RoomUDN", propChangeInfo);
            }
            if (roomState.volume != roomStateLocal.volume)
            {
            roomState.volume = roomStateLocal.volume;
            someStateChanged = true;
            AddPropChangeInfo("RoomState", propChangeInfo);
            }
            if (roomState.mute != roomStateLocal.mute)
            {
            roomState.mute = roomStateLocal.mute;
            someStateChanged = true;
            AddPropChangeInfo("RoomMute", propChangeInfo);
            }

            roomStateMap.insert(std::make_pair(roomState.roomUDN, roomState));
            }

            }
            catch (OpenHome::Exception &ex)
            {
            this->UPNPException(ex, __FUNCTION__);
            }
            catch (std::exception &ex)
            {
            this->Log(LogType::LOGERROR, ex.what(), __FUNCTION__);
            }

            // if soemthing has changed we do signal the subscribers
            if (someStateChanged)
            {
            // each update of the zones we generate and store a random number
            // this is needed for JSON webserver for long polling action on zone information
            boost::uint32_t curUpdateId = Utils::GetRandomNumber();
            if (managerList.deviceManager->GetLastUpdateIdRendererState() == curUpdateId)
            curUpdateId++;
            managerList.deviceManager->SetLastUpdateIdRendererState(curUpdateId);

            this->Log(LogType::LOGDEBUG, "Properties Changed: " + propChangeInfo + " (" + this->GetIdentificationString() + ")", __FUNCTION__);
            signalMediaRendererStateChanged(this->UDN);
            }

            }
            */

        }
    }
}
